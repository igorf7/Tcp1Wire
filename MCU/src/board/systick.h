/*!
 \file   systick.h
 \date   November-2024 (created)
 \brief  SysTick driver header file
*/
#ifndef SYSTICK_H
#define SYSTICK_H

#include "stm32f10x.h"
#include "stddef.h"

/* API */
void InitSystickTimer(void (*callback)(void));
void StartSystickTimer(uint32_t ms);
void StopSystickTimer(void);
#endif // SYSTICK_H
