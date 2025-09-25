/*!
 \file   main.h
 \brief  main application module header file
*/
#ifndef __MAIN_H
#define __MAIN_H

#include "stm32f10x.h"
#include "led.h"
#include "usart.h"

#define IWDG_WA_Enable      ((uint16_t)0x5555)
#define IWDG_WA_Disable     ((uint16_t)0x0000)
#define KR_KEY_Reload       ((uint16_t)0xAAAA)
#define KR_KEY_Enable       ((uint16_t)0xCCCC)
#define WatchdogReload(key) (IWDG->KR = key)

__STATIC_INLINE void InitWatchdog(void)
{
    IWDG->KR = IWDG_WA_Enable;
    IWDG->PR = 0x02;
    IWDG->RLR = 0x0FFF;
    IWDG->KR = KR_KEY_Reload;
    IWDG->KR = KR_KEY_Enable;
}

/* Callbacks */
void BackgroundTask(void);
void onUartError(uint16_t err_code);
void onUartRxComplete(UartBuffer_t *buff);
#endif  // __MAIN_H
