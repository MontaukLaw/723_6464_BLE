#ifndef _USER_COMM_H_
#define _USER_COMM_H_

#include "main.h"
#include "adc.h"
#include "dma.h"
#include "fdcan.h"
#include "i2c.h"
#include "memorymap.h"
#include "usart.h"
#include "gpio.h"
#include "app.h"
#include "stm32h723xx.h"
#include "switch_hal.h"
#include "delay.h"
#include "sys.h"
#include "sys_dma.h"
#include "sys_mpu.h"

typedef struct
{
    GPIO_TypeDef *port;
    uint16_t pin;
} GPIO_Channel;

#define CH_DEF(n) {VOUT_##n##_GPIO_Port, VOUT_##n##_Pin}

#define INPUT_CH_NUMBER 64
#define ADC_CHANNEL_NUMBER 64

#define TOTAL_POINTS (INPUT_CH_NUMBER * ADC_CHANNEL_NUMBER)
#define ADC_BUFFER_SIZE 2 // 10
#define ADC_BUFFER_START 5

#define FRAME_TAIL_LEN 4
#define FRAME_LEN (TOTAL_POINTS + FRAME_TAIL_LEN)

#define ZERO_VAL  45

#endif
