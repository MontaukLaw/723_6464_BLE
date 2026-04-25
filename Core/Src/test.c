#include "user_comm.h"

void test_task(void)
{

    uint16_t input_idx = 0;
    uint16_t adc_idx = 0;
    uint16_t point_nmb = 0;

    memset(points_data, 0, sizeof(uint8_t) * FRAME_LEN);
    init_frame_tail();

    for (input_idx = 32; input_idx < ADC_CHANNEL_NUMBER; input_idx++)
    {
        // 打开通道
        set_channel_pin(input_idx, GPIO_PIN_SET);

        for (adc_idx = 32; adc_idx < ADC_CHANNEL_NUMBER; adc_idx++)
        {

            point_nmb = input_idx * ADC_CHANNEL_NUMBER + adc_idx;

            // 切换adc通道
            set_adc_ch(adc_idx);

            // 1.6us可以做10次adc了
            // delay_ns(ADC_SETTLE_NS);
            delay_ns(6000);
            // points_data[point_nmb] = adc_dma_buffer[2];

            // 取最大值
            uint16_t adc_max = 0;
            for (uint32_t i = 0; i < ADC_BUFFER_SIZE; i++)
            {
                if (adc_dma_buffer[i] > adc_max)
                {
                    adc_max = adc_dma_buffer[i];
                }
            }
            points_data[point_nmb] = (uint8_t)adc_max;
            // if (adc_max <= ZERO_VAL)
            // {
            //     points_data[point_nmb] = 0;
            // }
            // else
            // {
            //     points_data[point_nmb] = (uint8_t)(adc_max - ZERO_VAL);
            // }

            point_nmb++;
        }

        // 关闭通道
        set_channel_pin(input_idx, GPIO_PIN_RESET);
    }

    // 发送数据
    // frame_submit_async();
    memcpy(tx_buf, points_data, FRAME_LEN);
    uart_send();
    while (uart_busy)
        ;
}
