/*!
 \file   onewire.h
 \brief  1-wire abstract device driver header file
 */
#ifndef __ONEWIRE_H
#define __ONEWIRE_H

#include "stm32f10x.h"
#include "timer.h"
#include "stdbool.h"

#define OW_SEARCHROM_CMD	0xF0
#define OW_ROM_SIZE			8U

/* API */
void OW_InitBus(void);
uint8_t OW_ReadByte(void);
void OW_WriteByte(uint8_t dt);
uint8_t OW_Reset(void);
bool OW_SearchRom(uint8_t *address);
void OW_ClearSearchResult(void);
#endif // __ONEWIRE_H
