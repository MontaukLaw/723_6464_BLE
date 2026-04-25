#include "user_comm.h"

const GPIO_Channel channels[64] = {
    CH_DEF(0), CH_DEF(1), CH_DEF(2), CH_DEF(3), CH_DEF(4), CH_DEF(5), CH_DEF(6), CH_DEF(7),
    CH_DEF(8), CH_DEF(9), CH_DEF(10), CH_DEF(11), CH_DEF(12), CH_DEF(13), CH_DEF(14), CH_DEF(15),
    CH_DEF(16), CH_DEF(17), CH_DEF(18), CH_DEF(19), CH_DEF(20), CH_DEF(21), CH_DEF(22), CH_DEF(23),
    CH_DEF(24), CH_DEF(25), CH_DEF(26), CH_DEF(27), CH_DEF(28), CH_DEF(29), CH_DEF(30), CH_DEF(31),
    CH_DEF(32), CH_DEF(33), CH_DEF(34), CH_DEF(35), CH_DEF(36), CH_DEF(37), CH_DEF(38), CH_DEF(39),
    CH_DEF(40), CH_DEF(41), CH_DEF(42), CH_DEF(43), CH_DEF(44), CH_DEF(45), CH_DEF(46), CH_DEF(47),
    CH_DEF(48), CH_DEF(49), CH_DEF(50), CH_DEF(51), CH_DEF(52), CH_DEF(53), CH_DEF(54), CH_DEF(55),
    CH_DEF(56), CH_DEF(57), CH_DEF(58), CH_DEF(59), CH_DEF(60), CH_DEF(61), CH_DEF(62), CH_DEF(63)};

static inline void gpio_write_pin_fast(GPIO_TypeDef *port, uint16_t pin, GPIO_PinState pin_status)
{
    port->BSRR = (pin_status == GPIO_PIN_SET) ? pin : ((uint32_t)pin << 16U);
}

void set_channel_pin(uint16_t ch, GPIO_PinState pin_status)
{
    if (ch < sizeof(channels) / sizeof(channels[0]))
    {
        gpio_write_pin_fast(channels[ch].port, channels[ch].pin, pin_status);
    }
}

void turn_gpio_to_input(GPIO_Channel channel)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = channel.pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(channel.port, &GPIO_InitStruct);
}

void turn_on_input_ch(uint16_t input_ch)
{
    // 设置所有通道为模拟输入
    uint16_t i;
    for (i = 0; i < INPUT_CH_NUMBER; i++)
    {
        turn_gpio_to_input(channels[i]);
    }

    // 设置指定通道为输出
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = channels[input_ch].pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(channels[input_ch].port, &GPIO_InitStruct);

    // 打开指定通道
    set_channel_pin(input_ch, GPIO_PIN_SET);
}

void turn_off_input_ch(uint16_t input_ch)
{

    // 关闭指定通道
    set_channel_pin(input_ch, GPIO_PIN_RESET);

    // 设置指定通道为模拟输入
    turn_gpio_to_input(channels[input_ch]);
}

static void close_all_adc_ch(void)
{
    gpio_write_pin_fast(SW_IN_EN_1_GPIO_Port, SW_IN_EN_1_Pin, GPIO_PIN_SET);
    gpio_write_pin_fast(SW_IN_EN_2_GPIO_Port, SW_IN_EN_2_Pin, GPIO_PIN_SET);
    gpio_write_pin_fast(SW_IN_EN_3_GPIO_Port, SW_IN_EN_3_Pin, GPIO_PIN_SET);
    gpio_write_pin_fast(SW_IN_EN_4_GPIO_Port, SW_IN_EN_4_Pin, GPIO_PIN_SET);
}

void set_adc_ch(uint16_t adc_ch)
{
    close_all_adc_ch();

    uint16_t adc_ch_idx = adc_ch % 16;

    if (adc_ch < 16)
    {
        // SW_IN_S0_1_GPIO_Port
        gpio_write_pin_fast(SW_IN_S0_1_GPIO_Port, SW_IN_S0_1_Pin, (adc_ch_idx & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        gpio_write_pin_fast(SW_IN_S1_1_GPIO_Port, SW_IN_S1_1_Pin, (adc_ch_idx & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        gpio_write_pin_fast(SW_IN_S2_1_GPIO_Port, SW_IN_S2_1_Pin, (adc_ch_idx & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        gpio_write_pin_fast(SW_IN_S3_1_GPIO_Port, SW_IN_S3_1_Pin, (adc_ch_idx & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);
       
        gpio_write_pin_fast(SW_IN_EN_1_GPIO_Port, SW_IN_EN_1_Pin, GPIO_PIN_RESET);
    }
    else if (adc_ch < 32)
    {
        gpio_write_pin_fast(SW_IN_S0_2_GPIO_Port, SW_IN_S0_2_Pin, (adc_ch_idx & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        gpio_write_pin_fast(SW_IN_S1_2_GPIO_Port, SW_IN_S1_2_Pin, (adc_ch_idx & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        gpio_write_pin_fast(SW_IN_S2_2_GPIO_Port, SW_IN_S2_2_Pin, (adc_ch_idx & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        gpio_write_pin_fast(SW_IN_S3_2_GPIO_Port, SW_IN_S3_2_Pin, (adc_ch_idx & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);
      
        gpio_write_pin_fast(SW_IN_EN_2_GPIO_Port, SW_IN_EN_2_Pin, GPIO_PIN_RESET);
    }
    else if (adc_ch < 48)
    {
        gpio_write_pin_fast(SW_IN_S0_3_GPIO_Port, SW_IN_S0_3_Pin, (adc_ch_idx & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        gpio_write_pin_fast(SW_IN_S1_3_GPIO_Port, SW_IN_S1_3_Pin, (adc_ch_idx & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        gpio_write_pin_fast(SW_IN_S2_3_GPIO_Port, SW_IN_S2_3_Pin, (adc_ch_idx & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        gpio_write_pin_fast(SW_IN_S3_3_GPIO_Port, SW_IN_S3_3_Pin, (adc_ch_idx & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);

        gpio_write_pin_fast(SW_IN_EN_3_GPIO_Port, SW_IN_EN_3_Pin, GPIO_PIN_RESET);
    }
    else if (adc_ch < 64)
    {
        gpio_write_pin_fast(SW_IN_S0_4_GPIO_Port, SW_IN_S0_4_Pin, (adc_ch_idx & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        gpio_write_pin_fast(SW_IN_S1_4_GPIO_Port, SW_IN_S1_4_Pin, (adc_ch_idx & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        gpio_write_pin_fast(SW_IN_S2_4_GPIO_Port, SW_IN_S2_4_Pin, (adc_ch_idx & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        gpio_write_pin_fast(SW_IN_S3_4_GPIO_Port, SW_IN_S3_4_Pin, (adc_ch_idx & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);

        gpio_write_pin_fast(SW_IN_EN_4_GPIO_Port, SW_IN_EN_4_Pin, GPIO_PIN_RESET);
    }
}
