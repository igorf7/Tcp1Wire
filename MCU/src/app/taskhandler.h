/*!
 \file   taskhandler.h
 \brief  task handler header file
*/
#ifndef __TASKHANDLER_H
#define __TASKHANDLER_H

#include "stm32f10x.h"
#include "onewire.h"
#include "string.h"

#define SCRATCHPAD_SIZE		8U

/* Device Opcodes */
typedef enum
{
    eOwSearchRom = (uint8_t)1,
    eOwBusReset,
    eOwBusWrite,
    eOwBusRead
} AppLayerOpcode_t;

/* Application Layer Packet Structure */
typedef struct
{
    uint8_t opcode;     // comand code
    uint8_t data_size;  // data field size
    uint8_t data[];		// data field address
} AppLayerPacket_t;

__STATIC_INLINE void Wait_ticks(volatile uint32_t nCount)
{
    for (; nCount != 0; nCount--);
}

/* API */
void TaskSearchRom(void *prm);
void TaskBusReset(void *prm);
void TaskBusWrite(void *prm);
void TaskBusRead(void *prm);
#endif // __TASKHANDLER_H
