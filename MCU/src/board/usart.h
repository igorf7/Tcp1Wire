/*!
 \file   usart.h
 \brief  USART driver header file
 */
#ifndef __USART_H
#define __USART_H

#include "stm32f10x.h"

#define USART_ETH	USART1 // Used USART module for UART/ETH converter

#define UART_MEM_SIZE  128U

#ifndef NULL
    #define NULL (void*)0U
#endif

/*!
 \brief UART buffer struture
 */
typedef struct {
    uint16_t data_size;
    uint8_t *data;
} UartBuffer_t;

/*!
 \brief Pointers to UART driver callbacks
 */
typedef struct {
    void(*uartError)(uint16_t err);
    void(*uartRxByte)(uint8_t data);
    void(*uartRxComplete)(UartBuffer_t *buff);
    void(*uartTxReady)(void);
    void(*uartTxComplete)(void);
} UartEvents_t;

/* API */
void InitUart(USART_TypeDef *USARTx, uint32_t br, UartEvents_t *events);
void UsartTransmit(USART_TypeDef *USARTx, uint8_t *data, int16_t len);
void SysTick_Callback(void);
#endif  // __USART_H
