/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SW_IN_S1_1_Pin GPIO_PIN_2
#define SW_IN_S1_1_GPIO_Port GPIOE
#define SW_IN_S3_1_Pin GPIO_PIN_3
#define SW_IN_S3_1_GPIO_Port GPIOE
#define SW_IN_S2_1_Pin GPIO_PIN_4
#define SW_IN_S2_1_GPIO_Port GPIOE
#define SW_IN_EN_1_Pin GPIO_PIN_5
#define SW_IN_EN_1_GPIO_Port GPIOE
#define SW_IN_S0_2_Pin GPIO_PIN_6
#define SW_IN_S0_2_GPIO_Port GPIOE
#define SW_IN_S1_2_Pin GPIO_PIN_13
#define SW_IN_S1_2_GPIO_Port GPIOC
#define SW_IN_S3_2_Pin GPIO_PIN_14
#define SW_IN_S3_2_GPIO_Port GPIOC
#define SW_IN_S2_2_Pin GPIO_PIN_15
#define SW_IN_S2_2_GPIO_Port GPIOC
#define SW_IN_EN_2_Pin GPIO_PIN_0
#define SW_IN_EN_2_GPIO_Port GPIOF
#define SW_IN_S0_3_Pin GPIO_PIN_1
#define SW_IN_S0_3_GPIO_Port GPIOF
#define SW_IN_S1_3_Pin GPIO_PIN_2
#define SW_IN_S1_3_GPIO_Port GPIOF
#define SW_IN_S3_3_Pin GPIO_PIN_3
#define SW_IN_S3_3_GPIO_Port GPIOF
#define SW_IN_S2_3_Pin GPIO_PIN_4
#define SW_IN_S2_3_GPIO_Port GPIOF
#define SW_IN_EN_3_Pin GPIO_PIN_5
#define SW_IN_EN_3_GPIO_Port GPIOF
#define SW_IN_S0_4_Pin GPIO_PIN_6
#define SW_IN_S0_4_GPIO_Port GPIOF
#define SW_IN_S1_4_Pin GPIO_PIN_7
#define SW_IN_S1_4_GPIO_Port GPIOF
#define SW_IN_S3_4_Pin GPIO_PIN_8
#define SW_IN_S3_4_GPIO_Port GPIOF
#define SW_IN_S2_4_Pin GPIO_PIN_9
#define SW_IN_S2_4_GPIO_Port GPIOF
#define SW_IN_EN_4_Pin GPIO_PIN_10
#define SW_IN_EN_4_GPIO_Port GPIOF
#define VOUT_5_Pin GPIO_PIN_0
#define VOUT_5_GPIO_Port GPIOC
#define VOUT_4_Pin GPIO_PIN_2
#define VOUT_4_GPIO_Port GPIOC
#define VOUT_3_Pin GPIO_PIN_3
#define VOUT_3_GPIO_Port GPIOC
#define VOUT_0_Pin GPIO_PIN_0
#define VOUT_0_GPIO_Port GPIOA
#define VOUT_1_Pin GPIO_PIN_1
#define VOUT_1_GPIO_Port GPIOA
#define VOUT_2_Pin GPIO_PIN_2
#define VOUT_2_GPIO_Port GPIOA
#define VOUT_6_Pin GPIO_PIN_3
#define VOUT_6_GPIO_Port GPIOA
#define VOUT_7_Pin GPIO_PIN_4
#define VOUT_7_GPIO_Port GPIOA
#define VOUT_8_Pin GPIO_PIN_5
#define VOUT_8_GPIO_Port GPIOA
#define VOUT_9_Pin GPIO_PIN_6
#define VOUT_9_GPIO_Port GPIOA
#define VOUT_10_Pin GPIO_PIN_7
#define VOUT_10_GPIO_Port GPIOA
#define VOUT_11_Pin GPIO_PIN_4
#define VOUT_11_GPIO_Port GPIOC
#define VOUT_12_Pin GPIO_PIN_5
#define VOUT_12_GPIO_Port GPIOC
#define VOUT_13_Pin GPIO_PIN_0
#define VOUT_13_GPIO_Port GPIOB
#define VOUT_14_Pin GPIO_PIN_1
#define VOUT_14_GPIO_Port GPIOB
#define VOUT_15_Pin GPIO_PIN_2
#define VOUT_15_GPIO_Port GPIOB
#define VOUT_16_Pin GPIO_PIN_11
#define VOUT_16_GPIO_Port GPIOF
#define VOUT_17_Pin GPIO_PIN_12
#define VOUT_17_GPIO_Port GPIOF
#define VOUT_18_Pin GPIO_PIN_13
#define VOUT_18_GPIO_Port GPIOF
#define VOUT_19_Pin GPIO_PIN_14
#define VOUT_19_GPIO_Port GPIOF
#define VOUT_20_Pin GPIO_PIN_15
#define VOUT_20_GPIO_Port GPIOF
#define VOUT_21_Pin GPIO_PIN_0
#define VOUT_21_GPIO_Port GPIOG
#define VOUT_22_Pin GPIO_PIN_1
#define VOUT_22_GPIO_Port GPIOG
#define VOUT_23_Pin GPIO_PIN_7
#define VOUT_23_GPIO_Port GPIOE
#define VOUT_24_Pin GPIO_PIN_8
#define VOUT_24_GPIO_Port GPIOE
#define VOUT_25_Pin GPIO_PIN_9
#define VOUT_25_GPIO_Port GPIOE
#define VOUT_26_Pin GPIO_PIN_10
#define VOUT_26_GPIO_Port GPIOE
#define VOUT_27_Pin GPIO_PIN_11
#define VOUT_27_GPIO_Port GPIOE
#define VOUT_28_Pin GPIO_PIN_12
#define VOUT_28_GPIO_Port GPIOE
#define VOUT_29_Pin GPIO_PIN_13
#define VOUT_29_GPIO_Port GPIOE
#define VOUT_30_Pin GPIO_PIN_14
#define VOUT_30_GPIO_Port GPIOE
#define VOUT_31_Pin GPIO_PIN_15
#define VOUT_31_GPIO_Port GPIOE
#define VOUT_32_Pin GPIO_PIN_10
#define VOUT_32_GPIO_Port GPIOB
#define VOUT_33_Pin GPIO_PIN_11
#define VOUT_33_GPIO_Port GPIOB
#define VOUT_34_Pin GPIO_PIN_12
#define VOUT_34_GPIO_Port GPIOB
#define VOUT_35_Pin GPIO_PIN_13
#define VOUT_35_GPIO_Port GPIOB
#define VOUT_36_Pin GPIO_PIN_14
#define VOUT_36_GPIO_Port GPIOB
#define VOUT_37_Pin GPIO_PIN_15
#define VOUT_37_GPIO_Port GPIOB
#define VOUT_38_Pin GPIO_PIN_8
#define VOUT_38_GPIO_Port GPIOD
#define VOUT_39_Pin GPIO_PIN_9
#define VOUT_39_GPIO_Port GPIOD
#define VOUT_40_Pin GPIO_PIN_10
#define VOUT_40_GPIO_Port GPIOD
#define VOUT_41_Pin GPIO_PIN_11
#define VOUT_41_GPIO_Port GPIOD
#define VOUT_42_Pin GPIO_PIN_12
#define VOUT_42_GPIO_Port GPIOD
#define VOUT_43_Pin GPIO_PIN_13
#define VOUT_43_GPIO_Port GPIOD
#define VOUT_44_Pin GPIO_PIN_14
#define VOUT_44_GPIO_Port GPIOD
#define VOUT_45_Pin GPIO_PIN_15
#define VOUT_45_GPIO_Port GPIOD
#define VOUT_46_Pin GPIO_PIN_2
#define VOUT_46_GPIO_Port GPIOG
#define VOUT_47_Pin GPIO_PIN_3
#define VOUT_47_GPIO_Port GPIOG
#define VOUT_48_Pin GPIO_PIN_4
#define VOUT_48_GPIO_Port GPIOG
#define VOUT_49_Pin GPIO_PIN_5
#define VOUT_49_GPIO_Port GPIOG
#define VOUT_50_Pin GPIO_PIN_6
#define VOUT_50_GPIO_Port GPIOG
#define VOUT_51_Pin GPIO_PIN_7
#define VOUT_51_GPIO_Port GPIOG
#define VOUT_52_Pin GPIO_PIN_8
#define VOUT_52_GPIO_Port GPIOG
#define VOUT_53_Pin GPIO_PIN_6
#define VOUT_53_GPIO_Port GPIOC
#define VOUT_54_Pin GPIO_PIN_7
#define VOUT_54_GPIO_Port GPIOC
#define VOUT_55_Pin GPIO_PIN_8
#define VOUT_55_GPIO_Port GPIOC
#define VOUT_56_Pin GPIO_PIN_9
#define VOUT_56_GPIO_Port GPIOC
#define VOUT_57_Pin GPIO_PIN_8
#define VOUT_57_GPIO_Port GPIOA
#define VOUT_58_Pin GPIO_PIN_15
#define VOUT_58_GPIO_Port GPIOA
#define VOUT_59_Pin GPIO_PIN_10
#define VOUT_59_GPIO_Port GPIOC
#define VOUT_60_Pin GPIO_PIN_11
#define VOUT_60_GPIO_Port GPIOC
#define VOUT_61_Pin GPIO_PIN_12
#define VOUT_61_GPIO_Port GPIOC
#define VOUT_62_Pin GPIO_PIN_0
#define VOUT_62_GPIO_Port GPIOD
#define VOUT_63_Pin GPIO_PIN_1
#define VOUT_63_GPIO_Port GPIOD
#define VOUT_64_Pin GPIO_PIN_2
#define VOUT_64_GPIO_Port GPIOD
#define LED_B_Pin GPIO_PIN_3
#define LED_B_GPIO_Port GPIOD
#define LED_R_Pin GPIO_PIN_4
#define LED_R_GPIO_Port GPIOD
#define LED_G_Pin GPIO_PIN_5
#define LED_G_GPIO_Port GPIOD
#define KEY_Pin GPIO_PIN_6
#define KEY_GPIO_Port GPIOD
#define LED_Pin GPIO_PIN_7
#define LED_GPIO_Port GPIOD
#define FOR_TEST2_Pin GPIO_PIN_3
#define FOR_TEST2_GPIO_Port GPIOB
#define FOR_TEST1_Pin GPIO_PIN_4
#define FOR_TEST1_GPIO_Port GPIOB
#define SW_IN_S0_1_Pin GPIO_PIN_1
#define SW_IN_S0_1_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
