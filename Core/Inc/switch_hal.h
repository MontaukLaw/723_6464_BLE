#ifndef _SWITCH_HAL_H_
#define _SWITCH_HAL_H_  

void turn_on_input_ch(uint16_t input_ch);

void set_channel_pin(uint16_t ch, GPIO_PinState pin_status);

void set_adc_ch(uint16_t adc_ch);

void turn_off_input_ch(uint16_t input_ch);

#endif // _SWITCH_HAL_H_
