#ifndef _APP_H_
#define _APP_H_

void main_task_adc(void);

void main_task(void);

void uart_test(void);

void init_frame_tail(void);

void start_adc_dma(void);

void main_task_adc_first(void);

void frame_submit_async(void);

extern volatile uint8_t uart_busy;

extern volatile uint8_t points_data[];

extern uint16_t adc_dma_buffer[];

extern uint8_t tx_buf[];
#endif
