#include "user_comm.h"

void led_task(void)
{
    static uint32_t last_run_ts = 0;
    uint32_t current_ts = HAL_GetTick();
    if (current_ts - last_run_ts < 500)
        return;

    HAL_GPIO_TogglePin(LED_B_GPIO_Port, LED_B_Pin);
    // HAL_UART_Transmit_IT(&huart4, (uint8_t *)"LED Toggle\r\n", 12);
    last_run_ts = current_ts;
}