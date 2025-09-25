/*!
 \file   timer.h
 \brief  TIM driver
 */
#include "timer.h"

static RCC_ClocksTypeDef RCC_Clocks;

/*!
 \brief Initializes the TIM2 module
 */
void Tim2Init(void)
{
    RCC_GetClocksFreq(&RCC_Clocks);
    
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    TIM2->PSC = (uint16_t)(RCC_Clocks.HCLK_Frequency / 1000000) - 1;
    TIM2->CR1 = TIM_CR1_OPM;
}

/*!
 \brief Delay in microseconds
 \param [IN] delay time in microseconds
*/
void WaitMicrosec(uint16_t uSec)
{
    TIM2->CNT = 0;
    TIM2->ARR = uSec;
    TIM2->CR1 |= TIM_CR1_CEN;
    while(!(TIM2->SR & TIM_SR_UIF))
    {
    }
    TIM2->SR &= ~TIM_SR_UIF;
}

/*!
 \brief Delay in milliseconds
 \param [IN] delay time in milliseconds
*/
void WaitMillisec(uint16_t mSec)
{
    uint16_t i;
    
    for(i = 0; i < mSec; i++){
        WaitMicrosec(1000);
    }
}
