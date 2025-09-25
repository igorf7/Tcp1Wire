/*!
 \file   led.c
 \date   November-2024 (created)
 \brief  LED driver
*/
#include "led.h"

/*!
 \brief Initializes the LED port/pin
*/
void LED_Init(GPIO_TypeDef *led_port, uint16_t led_pin)
{
    GPIO_InitTypeDef portStruct;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    
    portStruct.GPIO_Pin = led_pin;
    portStruct.GPIO_Speed = GPIO_Speed_50MHz;
    portStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(led_port, &portStruct);
    LED_OFF(led_port, led_pin);
}

/*!
 \brief Blinks the LED
 \param [IN] LED port
 \param [IN] LED pin
 \param [IN] delay in ticks
*/
void LED_Blink(GPIO_TypeDef *led_port, uint16_t led_pin, volatile uint32_t ticks)
{
    LED_ON(led_port, led_pin);
    for (; ticks != 0; ticks--);
    LED_OFF(led_port, led_pin);
}
