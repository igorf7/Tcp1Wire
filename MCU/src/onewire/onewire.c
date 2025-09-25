/*!
 \file   onewire.c
 \brief  1-wire abstract device driver
 */
#include "onewire.h"

static bool LastDeviceFlag;
static uint8_t LastDiscrepancy;
static uint8_t SearchRom[8];

/*!
 \brief Reads a bit from the 1-Wire bus
 \retval bit state
 */
static uint8_t OW_ReadBit(void)
{
	uint8_t r_bit = 0;
	GPIOB->ODR &= ~GPIO_ODR_ODR11;
	WaitMicrosec(6);
	GPIOB->ODR |= GPIO_ODR_ODR11;
	WaitMicrosec(6);
	r_bit = (GPIOB->IDR & GPIO_IDR_IDR11 ? 1 : 0);
	WaitMicrosec(58);
	
	return r_bit;
}

/*!
 \brief Writes a bit to the 1-Wire bus
 \param bit state
 */
static void OW_WriteBit(uint8_t w_bit)
{
	GPIOB->ODR &= ~GPIO_ODR_ODR11;
	WaitMicrosec(w_bit ? 6 : 64);
	GPIOB->ODR |= GPIO_ODR_ODR11;
	WaitMicrosec(w_bit ? 60 : 10);
}

/*!
 \brief Initializes the 1-Wire bus
 */
void OW_InitBus(void)
{
	GPIO_DeInit(GPIOB);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIOB->CRH |= GPIO_CRH_MODE11;
	GPIOB->CRH |= GPIO_CRH_CNF11_0;
	GPIOB->CRH &= ~GPIO_CRH_CNF11_1;
	
	Tim2Init();
}

/*!
 \brief Reads a byte of data from the 1-Wire bus
 \retval Received data byte
 */
uint8_t OW_ReadByte(void)
{
	uint8_t data = 0;
	
	for (uint8_t i = 0; i < 8; i++) {
		data += OW_ReadBit() << i;
	}
	
	return data;
}

/*!
 \brief Writes a byte of data to the 1-Wire bus
 \param byte to Wrire
 */
void OW_WriteByte(uint8_t data)
{
	for (uint8_t i = 0; i < 8; i++) {
		OW_WriteBit(data >> i & 1);
	}
}

/*!
 \brief Performs the RESET function on the 1-Wire bus
 \retval operation status
 */
uint8_t OW_Reset(void)
{
	uint16_t status;
	GPIOB->ODR &= ~GPIO_ODR_ODR11;
	WaitMicrosec(480);
	GPIOB->ODR |= GPIO_ODR_ODR11;
	WaitMicrosec(70);
	status = GPIOB->IDR & GPIO_IDR_IDR11;
	WaitMicrosec(500);
	
	return (status ? 1 : 0);
}

/*!
 \brief Performs the SEARCHROM function on the 1-Wire bus
 \param pointer to a buffer for writing the found device address
 \retval true if successful, otherwise false
 */
bool OW_SearchRom(uint8_t *address)
{
    uint8_t id_bit_number       = 1,
            last_zero           = 0,
            rom_byte_number     = 0,
            rom_byte_mask       = 1,
            id_bit,
            cmp_id_bit,
            search_direction;
    
    bool search_result = false;
    
    if (!LastDeviceFlag) {
		OW_Reset();
		OW_WriteByte(OW_SEARCHROM_CMD);
    }
    
    do {
        id_bit = OW_ReadBit();		// read data bit on 1-Wire bus
        cmp_id_bit = OW_ReadBit();	// read data bit on 1-Wire bus
        
        if ((id_bit == 1) && (cmp_id_bit == 1)) {
			break;
        }
        else {
            if (id_bit != cmp_id_bit) {
                search_direction = id_bit; // bit write value for search
            }
            else {
                if (id_bit_number < LastDiscrepancy) {
                    search_direction = ((SearchRom[rom_byte_number] & rom_byte_mask) > 0);
                }
                else {
                    search_direction = (id_bit_number == LastDiscrepancy);
                }
                if (search_direction == 0) {
					last_zero = id_bit_number;
				}
            }
            if (search_direction == 1) {
				SearchRom[rom_byte_number] |= rom_byte_mask;
            }
			else {
				SearchRom[rom_byte_number] &= ~rom_byte_mask;
            }
            OW_WriteBit(search_direction);	// write data bit to the 1-Wire bus
			id_bit_number++;
			rom_byte_mask <<= 1;
            if (rom_byte_mask == 0) {
				rom_byte_number++;
				rom_byte_mask = 1;
			}
        }
    } while (rom_byte_number < 8);	// read bytes 0..7
    
    if (!(id_bit_number < 65)) {
        // Search successful 
        LastDiscrepancy = last_zero;
        // Check for last device
        if (LastDiscrepancy == 0) {
			LastDeviceFlag = true;
        }
		search_result = true;	
    }
    
    if (!search_result || !SearchRom[0]) {
		LastDiscrepancy = 0;
        LastDeviceFlag = false;
		search_result = false;
	}
    else {
        for (int i = 0; i < 8; i++) {
            address[i] = SearchRom[i];
        }
    }
    
    return search_result;
}

/*!
 \brief Clears the specified variables after searching
 */
void OW_ClearSearchResult(void)
{
    LastDeviceFlag = false;
    LastDiscrepancy = 0;
    
    for (int i = 0; i < 8; i++) {
        SearchRom[i] = 0;
    }
}
