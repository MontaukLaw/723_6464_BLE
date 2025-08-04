#include "user_comm.h"

volatile uint8_t adc_busy = 0; // ADC是否忙碌

volatile uint8_t counter = 0;

volatile uint8_t adc_val = 0;

volatile uint8_t time_to_change_adc_ch = 0;
volatile uint8_t frame_id = 0;
volatile uint16_t point_idx = 0;
volatile uint16_t input_ch = 0;
volatile uint16_t adc_ch = 0;
volatile uint8_t uart_busy = 0; // UART是否忙碌

__attribute__((section("dma_buffer"), aligned(32))) // uint8_t adc_dma_buffer[1000] = {0};
uint8_t adc_dma_buffer[ADC_BUFFER_SIZE] = {0};      // 现在大小是以 word 为单位

__attribute__((section("dma_buffer"), aligned(32))) // 用于存储点数据, 保存在CPU可以访问的区域
volatile uint8_t points_data[FRAME_LEN] = {0};

__attribute__((section("dma_buffer"), aligned(32)))
uint8_t tx_buf[4100] = {1, 2, 3, 4, 5};

static void uart_send(void)
{
    // counter++;
    // points_data[0] = counter; // 更新帧头
    // HAL_StatusTypeDef status = HAL_UART_Transmit_DMA(&huart4, tx_buf, 4100);
    HAL_StatusTypeDef status = HAL_UART_Transmit_DMA(&huart4, points_data, FRAME_LEN);
    uart_busy = 1;
    // HAL_GPIO_TogglePin(FOR_TEST1_GPIO_Port, FOR_TEST1_Pin);
    HAL_GPIO_WritePin(FOR_TEST1_GPIO_Port, FOR_TEST1_Pin, GPIO_PIN_SET);
}

void main_task_adc(void)
{
    if (HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adc_dma_buffer, ADC_BUFFER_SIZE) != HAL_OK)
    {
        // 启动DMA失败
        Error_Handler();
    }

    adc_busy = 1;
    while (adc_busy)
        ;
}

// 7uS
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    if (hadc->Instance == ADC1)
    {
        // HAL_GPIO_TogglePin(FOR_TEST1_GPIO_Port, FOR_TEST1_Pin);
        adc_busy = 0;
    }
}

void adc_data_handler(void)
{
    // 简单计算平均值
    uint32_t adc_sum = 0;
    for (uint32_t i = 0; i < ADC_BUFFER_SIZE; i++)
    {
        adc_sum += adc_dma_buffer[i];
    }
    // tx_buf[0] = adc_sum / ADC_BUFFER_SIZE; // 计算平均值
    float result = adc_sum / ADC_BUFFER_SIZE;

    if (result <= ZERO_VAL)
    {
        points_data[point_idx] = 0;
    }
    else
    {
        points_data[point_idx] = result - ZERO_VAL;
    }
    // points_data[point_idx] = adc_sum / (ADC_BUFFER_SIZE - 5) -  ;
}

// 切换输入通道
// 因为输入切换比较容易, 改gpio就行.
static void change_input_ch(void)
{
    input_ch++;
    if (input_ch >= INPUT_CH_NUMBER)
    {
        input_ch = 0;
        time_to_change_adc_ch = 1;
    }
}

// 切换adc通道
static void change_adc_ch(void)
{
    if (time_to_change_adc_ch == 0)
    {
        return;
    }

    // 切换adc通道
    set_adc_ch(adc_ch);

    adc_ch++;
    if (adc_ch >= ADC_CHANNEL_NUMBER)
    {
        adc_ch = 0;
    }

    time_to_change_adc_ch = 0;
}

// 切换数据索引
static void change_point_idx(void)
{
    point_idx++;

    if (point_idx >= TOTAL_POINTS)
    {

        uart_send();

        // points_data[0] = frame_id;
        // // HAL_UART_Transmit_DMA(&huart1, points_data, FRAME_LEN); // 发送点数据
        // HAL_UART_Transmit_DMA(&huart4, points_data, FRAME_LEN); // 发送点数据
        uart_busy = 1;
        // HAL_GPIO_WritePin(FOR_TEST1_GPIO_Port, FOR_TEST1_Pin, GPIO_PIN_SET);

        // delay_ms(20);
        point_idx = 0;
    }
}

void main_task(void)
{
    if (uart_busy)
    {
        return;
    }

    // 打开通道
    set_channel_pin(input_ch, GPIO_PIN_SET);

    delay_us(5);

    // 开启ADC
    if (HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adc_dma_buffer, ADC_BUFFER_SIZE) != HAL_OK)
    {
        // 启动DMA失败
        Error_Handler();
    }

    adc_busy = 1;
    while (adc_busy)
        ;
    // 关闭通道
    set_channel_pin(input_ch, GPIO_PIN_RESET);

    adc_data_handler();

    // 切换输入gpio, 这样速度最快
    change_input_ch();

    // 切换逻辑开关
    change_adc_ch();

    // 检查发送数据
    change_point_idx();
}

void init_frame_tail(void)
{

    // 初始化帧尾
    points_data[TOTAL_POINTS] = 0xAA;     // 帧尾第一个字节
    points_data[TOTAL_POINTS + 1] = 0x55; // 帧尾第二个字节
    points_data[TOTAL_POINTS + 2] = 0x03; // 帧尾第三个字节
    points_data[TOTAL_POINTS + 3] = 0x99; // 帧尾第四个字节
}

void uart_test(void)
{
    // if (uart_busy)
    // {
    //     return;
    // }

    uart_send();
    delay_ms(20);
    // counter++;
    // points_data[0] = counter; // 更新帧头
    // // HAL_StatusTypeDef status = HAL_UART_Transmit_DMA(&huart4, tx_buf, 4100);
    // HAL_StatusTypeDef status = HAL_UART_Transmit_DMA(&huart4, points_data, 4100);

    // if (status != HAL_OK)
    // {
    //     // printf("DMA启动失败: %d\r\n", status);
    //     delay_ms(10);
    // }
    // // HAL_UART_Transmit_IT(&huart4, tx_buf, 6, 0xFFFF);
    // delay_ms(10);
    // // HAL_Delay(1);
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)
    {
        // HAL_GPIO_TogglePin(FOR_TEST1_GPIO_Port, FOR_TEST1_Pin);
        HAL_GPIO_WritePin(FOR_TEST1_GPIO_Port, FOR_TEST1_Pin, GPIO_PIN_RESET);
        uart_busy = 0; // UART发送完成
    }
    else if (huart->Instance == UART4)
    {
        uart_busy = 0; // UART发送完成
        HAL_GPIO_WritePin(FOR_TEST1_GPIO_Port, FOR_TEST1_Pin, GPIO_PIN_RESET);
        // SCB_CleanDCache_by_Addr((uint32_t *)points_data, FRAME_LEN);
    }
}