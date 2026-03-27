/*!
 \file   usart.c
 \brief  USART driver
 */
#include "usart.h"

static UartEvents_t *uartEvents = NULL;
static UartBuffer_t uartBuffer;
static uint16_t errorCode = 0;
static uint8_t UartDataMemory[UART_MEM_SIZE];

/*!
 \brief Initializes the USART module
 \param [IN] USARTx module
 \param [IN] baudrate - USART baudrate
 \param [IN] events - USART events
 */
void InitUart(USART_TypeDef *USARTx, uint32_t baudrate, UartEvents_t *events)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    USART_InitTypeDef USART_InitStruct;
	IRQn_Type USARTx_IRQn;
	uint16_t usart_rx_pin, usart_tx_pin;
    
    uartEvents = events;
	uartBuffer.data = UartDataMemory;
    uartBuffer.data_size = 0;
    
    /* Init USART port */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	
	if (USARTx == USART1) {
		usart_rx_pin = GPIO_Pin_10;
		usart_tx_pin = GPIO_Pin_9;
		USARTx_IRQn = USART1_IRQn;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	}
	else if (USARTx == USART2) {
		usart_rx_pin = GPIO_Pin_3;
		usart_tx_pin = GPIO_Pin_2;
		USARTx_IRQn = USART2_IRQn;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	}
	else
        return;
    
    /* USART Rx as input floating */
    GPIO_InitStruct.GPIO_Pin = usart_rx_pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    /* USART Tx as alternate function push-pull */
    GPIO_InitStruct.GPIO_Pin = usart_tx_pin;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* Init USART */
    USART_InitStruct.USART_BaudRate = baudrate;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USARTx, &USART_InitStruct);
	
	USART_ClearFlag(USARTx, USART_FLAG_TC | USART_FLAG_RXNE);
	USART_ClearITPendingBit(USARTx, USART_IT_TC | USART_IT_RXNE);
    
    USARTx->CR1 |= USART_CR1_RXNEIE;    // USART RX not empty interrupt enable
    USARTx->CR3 |= USART_CR3_EIE;       // USART Error interrupt enable
    
    NVIC_SetPriority(USARTx_IRQn, 1);
    NVIC_EnableIRQ(USARTx_IRQn);
    
    USART_Cmd(USARTx, ENABLE);
}

/*!
 \brief Transmits data via USARTx
 \param [IN] USARTx module
 \param [IN] data - pointer to a data buffer
 \param [IN] len - lenght of data to transmit
 */
void UsartTransmit(USART_TypeDef *USARTx, uint8_t *data, int16_t len)
{
	USARTx->SR &= ~USART_FLAG_TC;
    while (len--) {
        while(!(USARTx->SR & USART_SR_TXE));
        USARTx->DR = *data++;
    }
    while(!(USARTx->SR & USART_SR_TC));
}

/*!
 \@brief USARTx interrupt handler routine
 \param [IN] USARTx module
 \note Possible if only one of the USART modules has interrupts enabled
 */
static void UsartHadler(USART_TypeDef *USARTx)
{
	/* USART Error interrupt */
    if ((USARTx->SR & 0x0F) != 0) {
        if (uartEvents->uartError != NULL) {
            errorCode |= (uint16_t)(USARTx->SR & 0x0F);
            uartBuffer.data[UART_MEM_SIZE-1] = USARTx->DR; // dummy read to clear flag
            uartEvents->uartError(errorCode);
        }
    }
    /* USART RX not empty interrupt */
    else if (USARTx->SR & USART_SR_RXNE) {
		if (uartBuffer.data_size >= UART_MEM_SIZE) {
			uartBuffer.data_size = 0;
		}
        else {
            uartBuffer.data[uartBuffer.data_size++] = USARTx->DR;
			if (uartBuffer.data_size == 1) USARTx->CR1 |= USART_CR1_IDLEIE;
        }
    }
	/* USART Idle line interrupt */
	else if (USARTx->SR & USART_SR_IDLE) {
		USARTx->CR1 &= ~USART_CR1_IDLEIE;
		if (uartEvents->uartRxComplete != NULL) {
			uartEvents->uartRxComplete(&uartBuffer);
		}
		uartBuffer.data_size = 0;
	}
}

/*!
 \@brief USART1 interrupt handler
 */
void USART1_IRQHandler(void)
{
	UsartHadler(USART1);
}

/*!
 \@brief USART2 interrupt handler
 */
void USART2_IRQHandler(void)
{
    UsartHadler(USART2);
}
