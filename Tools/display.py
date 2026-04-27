import sys
import time
import numpy as np
import serial
import serial.tools.list_ports

from PyQt6.QtCore import Qt, QThread, pyqtSignal
from PyQt6.QtWidgets import (
    QApplication, QWidget, QPushButton, QComboBox, QLabel,
    QHBoxLayout, QVBoxLayout, QMessageBox
)

import pyqtgraph as pg


FRAME_LEN = 4100
DATA_LEN = 4096
TAIL = b"\xAA\x55\x03\x99"
BAUDRATE = 6000000
TARGET_NAME = "USB-Enhanced-SERIAL CH343"
RENDER_SCALE = 8
DOT_SIGMA = 2.8
MAX_DISPLAY_FPS = 30.0


class SerialReader(QThread):
    frame_received = pyqtSignal(object)
    status = pyqtSignal(str)
    stats = pyqtSignal(float, int, int)

    def __init__(self, port: str):
        super().__init__()
        self.port = port
        self.running = True
        self.ser = None

    def run(self):
        try:
            self.ser = serial.Serial(
                self.port,
                BAUDRATE,
                timeout=0.02,
                write_timeout=0.02
            )
            self.status.emit(f"Connected: {self.port}")
        except Exception as e:
            self.status.emit(f"Open failed: {e}")
            return

        buf = bytearray()
        bytes_this_sec = 0
        frames_this_sec = 0
        last_print_time = time.time()
        last_emit_time = 0.0
        emit_interval = 1.0 / MAX_DISPLAY_FPS

        while self.running:
            try:
                data = self.ser.read(8192)
                if data:
                    buf.extend(data)
                    bytes_this_sec += len(data)

                now = time.time()
                if now - last_print_time >= 1.0:
                    elapsed = now - last_print_time
                    rx_fps = frames_this_sec / elapsed
                    self.stats.emit(rx_fps, bytes_this_sec, len(buf))
                    print(f"[RX] {bytes_this_sec} bytes/s, frames={rx_fps:.1f}/s, buffer={len(buf)}")
                    bytes_this_sec = 0
                    frames_this_sec = 0
                    last_print_time = now    

                while len(buf) >= FRAME_LEN:
                    frame = bytes(buf[:FRAME_LEN])

                    if frame[-4:] == TAIL:
                        payload = frame[:DATA_LEN]

                        frames_this_sec += 1
                        now = time.time()
                        if now - last_emit_time >= emit_interval:
                            arr = np.frombuffer(payload, dtype=np.uint8).reshape((64, 64)).copy()
                            self.frame_received.emit(arr)
                            last_emit_time = now

                        del buf[:FRAME_LEN]
                    else:
                        # 失步后寻找包尾，尽快重新同步
                        idx = buf.find(TAIL)
                        if idx >= 0:
                            next_start = idx + 4
                            del buf[:next_start]
                        else:
                            # 防止无限增长
                            if len(buf) > FRAME_LEN * 4:
                                del buf[:-FRAME_LEN]

            except Exception as e:
                self.status.emit(f"Read error: {e}")
                break

        try:
            if self.ser and self.ser.is_open:
                self.ser.close()
        except Exception:
            pass

        self.status.emit("Disconnected")

    def stop(self):
        self.running = False
        self.wait(1000)


def make_heat_lut():
    stops = np.array([0, 25, 70, 115, 165, 210, 255], dtype=np.float32)
    colors = np.array([
        [4, 9, 24],
        [18, 45, 100],
        [31, 120, 200],
        [142, 216, 255],
        [255, 209, 102],
        [249, 115, 22],
        [185, 28, 28],
    ], dtype=np.float32)

    x = np.arange(256, dtype=np.float32)
    lut = np.zeros((256, 3), dtype=np.ubyte)
    for channel in range(3):
        lut[:, channel] = np.interp(x, stops, colors[:, channel]).astype(np.ubyte)
    return lut


def gaussian_kernel_1d(sigma):
    radius = max(1, int(sigma * 3.0))
    x = np.arange(-radius, radius + 1, dtype=np.float32)
    return np.exp(-(x * x) / (2.0 * sigma * sigma)).astype(np.float32)


def blur_axis(arr, kernel, axis):
    radius = len(kernel) // 2
    pad_width = [(0, 0)] * arr.ndim
    pad_width[axis] = (radius, radius)
    padded = np.pad(arr, pad_width, mode="edge")

    out = np.zeros_like(arr, dtype=np.float32)
    for i, weight in enumerate(kernel):
        sl = [slice(None)] * arr.ndim
        sl[axis] = slice(i, i + arr.shape[axis])
        out += padded[tuple(sl)] * weight
    return out


def render_soft_dots(arr, scale, kernel):
    h, w = arr.shape
    image = np.zeros((h * scale, w * scale), dtype=np.float32)
    center = scale // 2
    image[center::scale, center::scale] = arr.astype(np.float32)
    image = blur_axis(image, kernel, axis=0)
    image = blur_axis(image, kernel, axis=1)
    return np.clip(image, 0, 255).astype(np.uint8)


class HeatmapWindow(QWidget):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("64x64 Serial Heatmap")
        self.resize(1300, 800)

        self.reader = None
        self.display_frame_count = 0
        self.total_display_frames = 0
        self.last_fps_time = time.time()
        self.display_fps = 0.0
        self.rx_fps = 0.0
        self.dot_kernel = gaussian_kernel_1d(DOT_SIGMA)

        self.init_ui()
        self.scan_ports()

    def init_ui(self):
        main_layout = QHBoxLayout(self)

        # 左侧热力图区域
        self.graphics = pg.GraphicsLayoutWidget()
        self.view = self.graphics.addViewBox()
        self.view.setAspectLocked(True)
        self.view.invertY(False)

        self.image_item = pg.ImageItem()
        self.image_item.setOpts(axisOrder="row-major")
        self.view.addItem(self.image_item)

        self.image_item.setLookupTable(make_heat_lut())
        self.image_item.setLevels([0, 255])

        # 初始化空图
        self.image_item.setImage(
            np.zeros((64 * RENDER_SCALE, 64 * RENDER_SCALE), dtype=np.uint8),
            autoLevels=False
        )

        # 右侧控制区
        panel = QWidget()
        panel.setFixedWidth(230)
        panel_layout = QVBoxLayout(panel)
        panel_layout.setAlignment(Qt.AlignmentFlag.AlignTop)

        title = QLabel("Serial Control")
        title.setObjectName("titleLabel")

        self.port_combo = QComboBox()

        self.scan_btn = QPushButton("扫描 CH343 串口")
        self.connect_btn = QPushButton("连接")
        self.disconnect_btn = QPushButton("断开")

        self.status_label = QLabel("Status: Idle")
        self.status_label.setWordWrap(True)

        self.rx_fps_label = QLabel("RX FPS: 0.0")
        self.display_fps_label = QLabel("Display FPS: 0.0")
        self.frame_label = QLabel("Displayed: 0")
        self.rx_status_label = QLabel("RX: 0 B/s, buffer=0")

        self.scan_btn.clicked.connect(self.scan_ports)
        self.connect_btn.clicked.connect(self.connect_serial)
        self.disconnect_btn.clicked.connect(self.disconnect_serial)

        panel_layout.addWidget(title)
        panel_layout.addSpacing(10)
        panel_layout.addWidget(QLabel("Port:"))
        panel_layout.addWidget(self.port_combo)
        panel_layout.addWidget(self.scan_btn)
        panel_layout.addSpacing(10)
        panel_layout.addWidget(self.connect_btn)
        panel_layout.addWidget(self.disconnect_btn)
        panel_layout.addSpacing(20)
        panel_layout.addWidget(self.rx_fps_label)
        panel_layout.addWidget(self.display_fps_label)
        panel_layout.addWidget(self.frame_label)
        panel_layout.addWidget(self.rx_status_label)
        panel_layout.addSpacing(20)
        panel_layout.addWidget(self.status_label)

        main_layout.addWidget(self.graphics, stretch=9)
        main_layout.addWidget(panel, stretch=1)

        self.setStyleSheet("""
            QWidget {
                background-color: #111318;
                color: #E8E8E8;
                font-size: 14px;
            }

            QLabel#titleLabel {
                font-size: 20px;
                font-weight: bold;
                color: #FFFFFF;
            }

            QComboBox {
                background-color: #1E222A;
                border: 1px solid #3A3F4B;
                border-radius: 8px;
                padding: 6px;
                color: white;
            }

            QPushButton {
                background-color: #2D6CDF;
                border: none;
                border-radius: 10px;
                padding: 10px;
                color: white;
                font-weight: bold;
            }

            QPushButton:hover {
                background-color: #3C7DFF;
            }

            QPushButton:pressed {
                background-color: #1E4FA8;
            }
        """)

    def scan_ports(self):
        self.port_combo.clear()

        ports = list(serial.tools.list_ports.comports())
        matched = []

        for p in ports:
            text = f"{p.device} - {p.description}"
            if TARGET_NAME.lower() in text.lower():
                matched.append((p.device, text))

        if not matched:
            self.status_label.setText("Status: 未找到 USB-Enhanced-SERIAL CH343")
            for p in ports:
                self.port_combo.addItem(f"{p.device} - {p.description}", p.device)
        else:
            for dev, text in matched:
                self.port_combo.addItem(text, dev)
            self.status_label.setText(f"Status: 找到 {len(matched)} 个 CH343 串口")

    def connect_serial(self):
        if self.reader is not None:
            QMessageBox.information(self, "Info", "已经连接")
            return

        port = self.port_combo.currentData()
        if not port:
            QMessageBox.warning(self, "Warning", "没有选择串口")
            return

        self.display_frame_count = 0
        self.total_display_frames = 0
        self.last_fps_time = time.time()
        self.rx_fps_label.setText("RX FPS: 0.0")
        self.display_fps_label.setText("Display FPS: 0.0")
        self.frame_label.setText("Displayed: 0")
        self.rx_status_label.setText("RX: 0 B/s, buffer=0")

        self.reader = SerialReader(port)
        self.reader.frame_received.connect(self.update_frame)
        self.reader.status.connect(self.update_status)
        self.reader.stats.connect(self.update_rx_stats)
        self.reader.start()

    def disconnect_serial(self):
        if self.reader:
            self.reader.stop()
            self.reader = None

    def update_status(self, text):
        self.status_label.setText(f"Status: {text}")
        if text == "Disconnected":
            self.reader = None

    def update_rx_stats(self, rx_fps, bytes_per_sec, buffer_len):
        self.rx_fps = rx_fps
        self.rx_fps_label.setText(f"RX FPS: {rx_fps:.1f}")
        self.rx_status_label.setText(f"RX: {bytes_per_sec} B/s, buffer={buffer_len}")

    def update_frame(self, arr):
        rendered = render_soft_dots(arr, RENDER_SCALE, self.dot_kernel)
        self.image_item.setImage(rendered, autoLevels=False)

        self.display_frame_count += 1
        self.total_display_frames += 1
        now = time.time()
        dt = now - self.last_fps_time

        if dt >= 1.0:
            self.display_fps = self.display_frame_count / dt
            self.display_fps_label.setText(f"Display FPS: {self.display_fps:.1f}")
            self.frame_label.setText(f"Displayed: {self.total_display_frames}")
            self.display_frame_count = 0
            self.last_fps_time = now

    def closeEvent(self, event):
        self.disconnect_serial()
        event.accept()


if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = HeatmapWindow()
    win.show()
    sys.exit(app.exec())
