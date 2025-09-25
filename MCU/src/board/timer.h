/*!
 \file   timer.h
 \brief  TIM driver header file
 */
#ifndef TIMER_H
#define TIMER_H

#include <stdbool.h>
#include "stm32f10x.h"

/* API */
void Tim2Init(void);
void WaitMicrosec(uint16_t uSec);
void WaitMillisec(uint16_t mSec);
#endif
