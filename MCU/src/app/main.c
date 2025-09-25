/*!
 \file   main.c
 \brief  main application module
*/
#include "main.h"
#include "scheduler.h"
#include "taskhandler.h"

static UartEvents_t uartEvents = 
    {NULL, NULL, NULL, NULL, NULL};

/*!
 \brief Program entry point
*/
int main(void)
{
    /* Program startup indicator */
    LED_Init(LED1_PORT, LED1_PIN);
    LED_Blink(LED1_PORT, LED1_PIN, 1000000);
    
    /* Initialize the task scheduler */
    InitTaskSheduler(&BackgroundTask);
    
    /* Initialize the 1-Wire Bus */
    OW_InitBus();
	
	/* Initialize USART module in UART mode */
	uartEvents.uartError = onUartError;
	uartEvents.uartRxComplete = onUartRxComplete;
	InitUart(USART_ETH, 115200, &uartEvents);
	
    /* Enable Watchdog */
    #ifndef DEBUG
    InitWatchdog();
    #endif
	
    __enable_irq();
    
    /* Mailoop */
    while (1)
	{
        RunTaskSheduler();
	}
}

/*!
 \brief Background task
*/
void BackgroundTask(void)
{
    /* Reload watchdog */
    #ifndef DEBUG
    WatchdogReload(KR_KEY_Reload);
    #endif
}

/*!
 \brief UART Error Callback Routine
*/
void onUartError(uint16_t err_code)
{
    // indicate USART error
}

/*!
 \brief UART receive callback function
*/
void onUartRxComplete(UartBuffer_t *buff)
{
	/* Check app layer opcode */
	switch (buff->data[0])
	{
		case eOwSearchRom:
			PutTask(TaskSearchRom, NULL);
			break;
		case eOwBusReset:
			PutTask(TaskBusReset, NULL);
			break;
		case eOwBusWrite:
			PutTask(TaskBusWrite, buff->data);
			break;
		case eOwBusRead:
			PutTask(TaskBusRead, buff->data);
			break;
		default:
			// wrong opcode
			break;
	}
}
