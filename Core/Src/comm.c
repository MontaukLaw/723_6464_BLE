#include "user_comm.h"

__attribute__((section("dma_buffer"), aligned(32)))
uint8_t uart4_rx_buf[STANDARD_PROTOCAL_LEN];
__IO uint8_t got_rx = 0;
__attribute__((section("dma_buffer"), aligned(32))) // 用于存储点数据, 保存在CPU可以访问的区域
volatile uint8_t uart4_tx_buf[FRAME_LEN] = {0};

void start_uart_rx(void)
{
    __HAL_UART_ENABLE_IT(&huart4, UART_IT_IDLE);
    __HAL_UART_CLEAR_IDLEFLAG(&huart4);

    HAL_UART_Receive_DMA(&huart4, uart4_rx_buf, UART_RX_BUF_LEN);
}

void uart4_it_handler(void)
{
    if (__HAL_UART_GET_FLAG(&huart4, UART_FLAG_IDLE) != RESET)
    {
        // 清除 IDLE 标志
        __HAL_UART_CLEAR_IDLEFLAG(&huart4);

        // 此时说明可能一帧数据接收完了
        // 获取当前 DMA 计数器剩余量, 计算本次接收字节数
        uint16_t remain = __HAL_DMA_GET_COUNTER(huart4.hdmarx);
        if (remain)
        {
            uint16_t data_len = UART_RX_BUF_LEN - remain;
            got_rx = data_len;
        }

        // 处理完毕后，可以选择清零或记录这段数据
        // 然后继续保持 DMA 接收，让它随时准备接收新的数据
        HAL_UART_AbortReceive(&huart4);
        // HAL_UART_DMAStop(&huart1);
        // 重新开启接收
        HAL_UART_Receive_DMA(&huart4, uart4_rx_buf, UART_RX_BUF_LEN);
    }
}

#define HARDWARE_VERSION 0x0911
void comm_handler(void)
{
    // 收到RTX中断
    // 收到RTX中断
    // if (got_rx && uart_sending == 0)
    // HC32F460 Unique ID:344637301550321299--Versions:c40510 -- company: JQ
    const uint8_t *src = (const uint8_t *)UID_BASE;

    if (got_rx)
    {
        if (uart4_rx_buf[got_rx - 2] == 0x0d && uart4_rx_buf[got_rx - 1] == 0x0a)
        {
            if (uart4_rx_buf[0] == 'A' && uart4_rx_buf[1] == 'T')
            {
                // uart4_tx_buf[0] = 'O';
                // uart4_tx_buf[1] = 'K';
                // uart4_tx_buf[2] = '\r';
                // uart4_tx_buf[3] = '\n';
                // sprintf((char *)uart4_tx_buf, "HC32F460 Unique ID:344637301550321299--Versions:%x -- company: JQ\r\n", HARDWARE_VERSION);
                sprintf((char *)uart4_tx_buf, "STM32H723 Unique ID:%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X -- Versions:%04x -- company: JQ\r\n",
                        src[0], src[1], src[2], src[3], src[4], src[5], src[6], src[7], src[8], src[9], src[10], src[11],
                        HARDWARE_VERSION);
                HAL_UART_Transmit_DMA(&huart4, uart4_tx_buf, strlen((char *)uart4_tx_buf));
                // HAL_UART_Transmit_DMA(&huart4, uart4_tx_buf, 4);
            }
        }
        got_rx = 0;
    }
}
