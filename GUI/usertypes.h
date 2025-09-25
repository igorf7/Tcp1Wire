#ifndef USERTYPES_H
#define USERTYPES_H

#include "qglobal.h"

#define DS18B20_SIGN_MASK	0xF800

const quint8 OW_SKIPROM_CMD = 0xCC;
const quint8 OW_MATCHROM_CMD = 0x55;
const quint8 OW_SEARCHROM_CMD = 0xF0;
const quint8 OW_WRITE_CMD = 0x4E;
const quint8 OW_READ_CMD = 0xBE;
const quint8 OW_CONVERT_CMD = 0x44;
const quint8 OW_RUN_SENSOR_CMD = 0x45;
const quint8 OW_SET_EEPROM_ADDRESS_CMD = 0x10;
const quint8 OW_GET_EEPROM_ADDRESS_CMD = 0x18;
const quint8 OW_WRITE_EEPROM_CMD = 0x48;
const quint8 OW_READ_EEPROM_CMD = 0xB8;
const quint8 OW_ERASE_EEPROM_CMD = 0x20;
const quint8 OW_READ_CRC8_REPLY_CMD = 0x14;
const quint8 OW_SET_DACS_CMD = 0x30;
const quint8 OW_RELOAD_CHIP_CMD = 0x40;
const quint8 OW_TEST_CRC16_CALIBR_TABLE_CMD = 0x50;
const quint8 OW_TEST_CRC16_RUN_SENSOR_CMD = 0x60;
const quint8 OW_GOTO_APP_CMD = 0x70;

/* Opcodes */
typedef enum
{
    eOwSearchRom = 1,
    eOwBusReset,
    eOwBusWrite,
    eOwBusRead
} TOpcode;

/* Application Layer Packet Structure */
typedef struct
{
    quint8 opcode;
    quint8 size;
    quint8 data[60];
} TAppLayerPacket;

#endif // USERTYPES_H
