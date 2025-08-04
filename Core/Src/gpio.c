/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
        * Free pins are configured automatically as Analog (this feature is enabled through
        * the Code Generation settings)
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, SW_IN_S1_1_Pin|SW_IN_S3_1_Pin|SW_IN_S2_1_Pin|SW_IN_S0_2_Pin
                          |VOUT_23_Pin|VOUT_24_Pin|VOUT_25_Pin|VOUT_26_Pin
                          |VOUT_27_Pin|VOUT_28_Pin|VOUT_29_Pin|VOUT_30_Pin
                          |VOUT_31_Pin|SW_IN_S0_1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(SW_IN_EN_1_GPIO_Port, SW_IN_EN_1_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, SW_IN_S1_2_Pin|SW_IN_S3_2_Pin|SW_IN_S2_2_Pin|VOUT_5_Pin
                          |VOUT_4_Pin|VOUT_3_Pin|VOUT_11_Pin|VOUT_12_Pin
                          |VOUT_53_Pin|VOUT_54_Pin|VOUT_55_Pin|VOUT_56_Pin
                          |VOUT_59_Pin|VOUT_60_Pin|VOUT_61_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, SW_IN_EN_2_Pin|SW_IN_EN_3_Pin|SW_IN_EN_4_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, SW_IN_S0_3_Pin|SW_IN_S1_3_Pin|SW_IN_S3_3_Pin|SW_IN_S2_3_Pin
                          |SW_IN_S0_4_Pin|SW_IN_S1_4_Pin|SW_IN_S3_4_Pin|SW_IN_S2_4_Pin
                          |VOUT_16_Pin|VOUT_17_Pin|VOUT_18_Pin|VOUT_19_Pin
                          |VOUT_20_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, VOUT_0_Pin|VOUT_1_Pin|VOUT_2_Pin|VOUT_6_Pin
                          |VOUT_7_Pin|VOUT_8_Pin|VOUT_9_Pin|VOUT_10_Pin
                          |VOUT_57_Pin|VOUT_58_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, VOUT_13_Pin|VOUT_14_Pin|VOUT_15_Pin|VOUT_32_Pin
                          |VOUT_33_Pin|VOUT_34_Pin|VOUT_35_Pin|VOUT_36_Pin
                          |VOUT_37_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, VOUT_21_Pin|VOUT_22_Pin|VOUT_46_Pin|VOUT_47_Pin
                          |VOUT_48_Pin|VOUT_49_Pin|VOUT_50_Pin|VOUT_51_Pin
                          |VOUT_52_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, VOUT_38_Pin|VOUT_39_Pin|VOUT_40_Pin|VOUT_41_Pin
                          |VOUT_42_Pin|VOUT_43_Pin|VOUT_44_Pin|VOUT_45_Pin
                          |VOUT_62_Pin|VOUT_63_Pin|VOUT_64_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, LED_B_Pin|LED_R_Pin|LED_G_Pin|LED_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, FOR_TEST2_Pin|FOR_TEST1_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : SW_IN_S1_1_Pin SW_IN_S3_1_Pin SW_IN_S2_1_Pin SW_IN_EN_1_Pin
                           SW_IN_S0_2_Pin VOUT_23_Pin VOUT_24_Pin VOUT_25_Pin
                           VOUT_26_Pin VOUT_27_Pin VOUT_28_Pin VOUT_29_Pin
                           VOUT_30_Pin VOUT_31_Pin SW_IN_S0_1_Pin */
  GPIO_InitStruct.Pin = SW_IN_S1_1_Pin|SW_IN_S3_1_Pin|SW_IN_S2_1_Pin|SW_IN_EN_1_Pin
                          |SW_IN_S0_2_Pin|VOUT_23_Pin|VOUT_24_Pin|VOUT_25_Pin
                          |VOUT_26_Pin|VOUT_27_Pin|VOUT_28_Pin|VOUT_29_Pin
                          |VOUT_30_Pin|VOUT_31_Pin|SW_IN_S0_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : SW_IN_S1_2_Pin SW_IN_S3_2_Pin SW_IN_S2_2_Pin */
  GPIO_InitStruct.Pin = SW_IN_S1_2_Pin|SW_IN_S3_2_Pin|SW_IN_S2_2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : SW_IN_EN_2_Pin SW_IN_S0_3_Pin SW_IN_S1_3_Pin SW_IN_S3_3_Pin
                           SW_IN_S2_3_Pin SW_IN_EN_3_Pin SW_IN_S0_4_Pin SW_IN_S1_4_Pin
                           SW_IN_S3_4_Pin SW_IN_S2_4_Pin SW_IN_EN_4_Pin VOUT_16_Pin
                           VOUT_17_Pin VOUT_18_Pin VOUT_19_Pin VOUT_20_Pin */
  GPIO_InitStruct.Pin = SW_IN_EN_2_Pin|SW_IN_S0_3_Pin|SW_IN_S1_3_Pin|SW_IN_S3_3_Pin
                          |SW_IN_S2_3_Pin|SW_IN_EN_3_Pin|SW_IN_S0_4_Pin|SW_IN_S1_4_Pin
                          |SW_IN_S3_4_Pin|SW_IN_S2_4_Pin|SW_IN_EN_4_Pin|VOUT_16_Pin
                          |VOUT_17_Pin|VOUT_18_Pin|VOUT_19_Pin|VOUT_20_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : VOUT_5_Pin VOUT_4_Pin VOUT_3_Pin VOUT_11_Pin
                           VOUT_12_Pin VOUT_53_Pin VOUT_54_Pin VOUT_55_Pin
                           VOUT_56_Pin VOUT_59_Pin VOUT_60_Pin VOUT_61_Pin */
  GPIO_InitStruct.Pin = VOUT_5_Pin|VOUT_4_Pin|VOUT_3_Pin|VOUT_11_Pin
                          |VOUT_12_Pin|VOUT_53_Pin|VOUT_54_Pin|VOUT_55_Pin
                          |VOUT_56_Pin|VOUT_59_Pin|VOUT_60_Pin|VOUT_61_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : VOUT_0_Pin VOUT_1_Pin VOUT_2_Pin VOUT_6_Pin
                           VOUT_7_Pin VOUT_8_Pin VOUT_9_Pin VOUT_10_Pin
                           VOUT_57_Pin VOUT_58_Pin */
  GPIO_InitStruct.Pin = VOUT_0_Pin|VOUT_1_Pin|VOUT_2_Pin|VOUT_6_Pin
                          |VOUT_7_Pin|VOUT_8_Pin|VOUT_9_Pin|VOUT_10_Pin
                          |VOUT_57_Pin|VOUT_58_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : VOUT_13_Pin VOUT_14_Pin VOUT_15_Pin VOUT_32_Pin
                           VOUT_33_Pin VOUT_34_Pin VOUT_35_Pin VOUT_36_Pin
                           VOUT_37_Pin FOR_TEST2_Pin FOR_TEST1_Pin */
  GPIO_InitStruct.Pin = VOUT_13_Pin|VOUT_14_Pin|VOUT_15_Pin|VOUT_32_Pin
                          |VOUT_33_Pin|VOUT_34_Pin|VOUT_35_Pin|VOUT_36_Pin
                          |VOUT_37_Pin|FOR_TEST2_Pin|FOR_TEST1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : VOUT_21_Pin VOUT_22_Pin VOUT_46_Pin VOUT_47_Pin
                           VOUT_48_Pin VOUT_49_Pin VOUT_50_Pin VOUT_51_Pin
                           VOUT_52_Pin */
  GPIO_InitStruct.Pin = VOUT_21_Pin|VOUT_22_Pin|VOUT_46_Pin|VOUT_47_Pin
                          |VOUT_48_Pin|VOUT_49_Pin|VOUT_50_Pin|VOUT_51_Pin
                          |VOUT_52_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : VOUT_38_Pin VOUT_39_Pin VOUT_40_Pin VOUT_41_Pin
                           VOUT_42_Pin VOUT_43_Pin VOUT_44_Pin VOUT_45_Pin
                           VOUT_62_Pin VOUT_63_Pin VOUT_64_Pin LED_B_Pin
                           LED_R_Pin LED_G_Pin LED_Pin */
  GPIO_InitStruct.Pin = VOUT_38_Pin|VOUT_39_Pin|VOUT_40_Pin|VOUT_41_Pin
                          |VOUT_42_Pin|VOUT_43_Pin|VOUT_44_Pin|VOUT_45_Pin
                          |VOUT_62_Pin|VOUT_63_Pin|VOUT_64_Pin|LED_B_Pin
                          |LED_R_Pin|LED_G_Pin|LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : KEY_Pin */
  GPIO_InitStruct.Pin = KEY_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(KEY_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PG10 PG13 PG15 */
  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_13|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pin : PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PE0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*AnalogSwitch Config */
  HAL_SYSCFG_AnalogSwitchConfig(SYSCFG_SWITCH_PC2, SYSCFG_SWITCH_PC2_CLOSE);

  /*AnalogSwitch Config */
  HAL_SYSCFG_AnalogSwitchConfig(SYSCFG_SWITCH_PC3, SYSCFG_SWITCH_PC3_CLOSE);

  /*AnalogSwitch Config */
  HAL_SYSCFG_AnalogSwitchConfig(SYSCFG_SWITCH_PA0, SYSCFG_SWITCH_PA0_CLOSE);

  /*AnalogSwitch Config */
  HAL_SYSCFG_AnalogSwitchConfig(SYSCFG_SWITCH_PA1, SYSCFG_SWITCH_PA1_CLOSE);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
