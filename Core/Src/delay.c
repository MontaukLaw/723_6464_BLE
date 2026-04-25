#include "sys.h"
#include "delay.h"

static uint32_t g_cpu_hz = 0;

void delay_init(uint16_t sysclk)
{
    uint32_t cpu_hz = SystemCoreClock;

    if (cpu_hz == 0U)
    {
        cpu_hz = (uint32_t)sysclk * 1000000UL;
    }

    g_cpu_hz = cpu_hz;

    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->LAR = 0xC5ACCE55UL;
    DWT->CYCCNT = 0U;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

void delay_us(uint32_t nus)
{
    uint64_t ticks_left;

    if (nus == 0U)
    {
        return;
    }

    if (((DWT->CTRL & DWT_CTRL_CYCCNTENA_Msk) == 0U) || (g_cpu_hz == 0U))
    {
        delay_init(0U);
    }

    ticks_left = (((uint64_t)nus * (uint64_t)g_cpu_hz) + 999999ULL) / 1000000ULL;
    while (ticks_left != 0ULL)
    {
        uint32_t start;
        uint32_t ticks = (ticks_left > 0x7FFFFFFFULL) ? 0x7FFFFFFFUL : (uint32_t)ticks_left;

        start = DWT->CYCCNT;
        while ((uint32_t)(DWT->CYCCNT - start) < ticks)
        {
            __NOP();
        }

        ticks_left -= ticks;
    }
}

void delay_ns(uint32_t nns)
{
    uint64_t ticks_left;

    if (nns == 0U)
    {
        return;
    }

    if (((DWT->CTRL & DWT_CTRL_CYCCNTENA_Msk) == 0U) || (g_cpu_hz == 0U))
    {
        delay_init(0U);
    }

    ticks_left = (((uint64_t)nns * (uint64_t)g_cpu_hz) + 999999999ULL) / 1000000000ULL;
    while (ticks_left != 0ULL)
    {
        uint32_t start;
        uint32_t ticks = (ticks_left > 0x7FFFFFFFULL) ? 0x7FFFFFFFUL : (uint32_t)ticks_left;

        start = DWT->CYCCNT;
        while ((uint32_t)(DWT->CYCCNT - start) < ticks)
        {
            __NOP();
        }

        ticks_left -= ticks;
    }
}

void delay_ms(uint16_t nms)
{
    while (nms-- != 0U)
    {
        delay_us(1000U);
    }
}
