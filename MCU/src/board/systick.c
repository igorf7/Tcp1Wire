/*!
 \file   systick.c
 \date   November-2024 (created)
 \brief  SysTick driver
*/
#include "systick.h"

static void (*SysTickEvent)(void);
static uint32_t count_1ms = 0;

/*!
 \brief Initializes the SysTick timer
 \param SysTick IRQ callback
*/
void InitSystickTimer(void (*callback)(void))
{
    SysTickEvent = callback;
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
    count_1ms = (float)SystemCoreClock/8000;
}

/*!
 \brief Starts the SysTick timer
 \param time interval (milliseconds)
*/
void StartSystickTimer(uint32_t ms)
{
    /* Reload the count value */
    SysTick->LOAD = ms * count_1ms;
    /* Clear the current count value */
    SysTick->VAL = 0x0000U;
    /* Enable the systick timer */
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
}

/*!
 \brief Stops the SysTick timer
*/
void StopSystickTimer(void)
{
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
    SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;
    /* Clear the current count value */
    SysTick->VAL = 0x0000U;
}

/*!
 \brief SysTick timer interrupt handler
*/
void SysTick_Handler(void)
{
    if (SysTickEvent != NULL) SysTickEvent();
}
