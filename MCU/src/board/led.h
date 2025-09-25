/*!
 \file   led.h
 \date   November-2024 (created)
 \brief  LED driver header file
*/
#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"

#define BLU_PILL_PLUS

#ifdef BLU_PILL_PLUS
    #define LED1_PORT   GPIOB
    #define LED1_PIN    (0x01 << 2) // pin 2
    #define LED_ON(led_port, led_pin)       (led_port->BSRR = led_pin)
    #define LED_OFF(led_port, led_pin)      (led_port->BRR = led_pin)
#else
    #define LED1_PORT   GPIOC
    #define LED1_PIN    (0x01 << 13) // pin 13
    #define LED_ON(led_port, led_pin)       (led_port->BRR = led_pin)
    #define LED_OFF(led_port, led_pin)      (led_port->BSRR = led_pin)
#endif

#define LED_TOGGLE(led_port, led_pin)   (led_port->ODR ^= led_pin)

void LED_Init(GPIO_TypeDef *led_port, uint16_t led_pin);
void LED_Blink(GPIO_TypeDef *led_port, uint16_t led_pin, volatile uint32_t ticks);
#endif // __LED_H
