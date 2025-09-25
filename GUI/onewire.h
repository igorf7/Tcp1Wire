#ifndef ONEWIRE_H
#define ONEWIRE_H

#include "usertypes.h"
#include <QObject>
#include <QMap>
#include <QHash>

class OneWire : public QObject
{
    Q_OBJECT

public:
    static QString &getName(quint8 family);
    static QString &getDescription(quint8 family);
    static quint8 getFamily(const QString &name);
    static quint8 calcCrc8(quint8 *data, quint16 size);

private:
    /* Supported devices */
    static const inline QMap<QString, quint8> deviceMap =
        {
            {"DS1990A", 0x01},  // 64-bit unique serial number
            {"DS1991", 0x02},   // 2048 bits of nonvolatile read/write memory
            {"DS1994", 0x04},   // 4096 bit read/write nonvolatile memory
            {"DS2405", 0x05},   // Addressable Switch with controlled open drain PIO pin
            {"DS1993", 0x06},   // 4096 bit read/write nonvolatile memory
            {"DS1992", 0x08},   // 1024 bit read/write nonvolatile memory
            {"DS1982", 0x09},   // 1024 bit Electrically Programmable Read Only Memory
            {"DS1995", 0x0A},   // 16384 bit read/write nonvolatile memory
            {"DS1985", 0x0B},   // 16384 bit Electrically Programmable Read Only Memory
            {"DS1996", 0x0C},   // 65536 bit read/write nonvolatile memory
            {"DS1986", 0x0F},   // 65536 bit Electrically Programmable Read Only Memory
            {"DS18S20", 0x10},  // Digital thermometer -55C to 125C 9 bit resolution
            {"DS2406", 0x12},   // 1-Wire Dual Addressable Switch
            {"DS1983", 0x13},   // 4096 bit Electrically Programmable Read Only Memory
            {"DS1971", 0x14},   // Electrically Erasable Programmable Read Only Memory
            {"DS1963S", 0x18},  // 4096 bits of read/write nonvolatile memory
            {"DS1963L", 0x1A},  // 4096 bit read/write nonvolatile memory
            {"DS28E04", 0x1C},  // Addressable 1-Wire 4K-bit EEPROM
            {"DS2423", 0x1D},   // 1-Wire counter with 4096 bits of read/write
            {"DS2409", 0x1F},   // 1-Wire Network Coupler with dual addressable
            {"DS2450", 0x20},   // Four high-impedance inputs for measurement of analog voltages
            {"DS1921", 0x21},   // Thermochron
            {"DS1822", 0x22},   // Digital thermometer -55C to 125C 12 bit resolution
            {"DS1973", 0x23},   // EEPROM 4096 bits
            {"DS2415", 0x24},   // Real time clock
            {"DS2438", 0x26},   // Smart Battery Monitor
            {"DS2417", 0x27},   // Real time clock with interrupt
            {"DS18B20", 0x28},  // Digital thermometer -55C to 125C 12 bit resolution
            {"DS2408", 0x29},   // 1-Wire 8-Channel Addressable Switch
            {"DS2890", 0x2C},   // 1-Wire linear taper digitally controlled potentiometer with 256 wiper positions
            {"DS1972", 0x2D},   // 1K-Bit protected 1-Wire EEPROM
            {"DS2760", 0x30},   // 1-Cell Li-Ion Battery Monitor
            {"DS1961S", 0x33},  // 1K-Bit protected 1-Wire EEPROM with SHA-1 Engine
            {"DS1977", 0x37},   // 32KB password protected memory
            {"DS2413", 0x3A},   // Dual Channel Addressable Switch
            {"DS1923", 0x41},   // Hygrochron
            {"DS28EA00", 0x42}, // Programmable resolution digital thermometer with 'sequence detect'
            {"DS28EC20", 0x43}, // 20Kb 1-Wire EEPROM
            {"DD84-MDR", 0x55}, // DD84 pressure sensor with MDR32 MCU
            {"DD84-GD", 0x58}   // DD84 pressure sensor with GD32 MCU
    };

    /* Device description */
    static const inline QHash<quint8, QString> description =
        {
            {0x01, "64-bit unique serial number.\n"},
            {0x02, "2048 bits of nonvolatile read/write memory organized as three \nsecure keys of 384 bits each and a 512 bit scratch pad.\n"},
            {0x04, "4096 bit read/write nonvolatile memory partitioned into sixteen \npages of 256 bits each and a real time clock/calendar in binary format.\n"},
            {0x05, "Addressable Switch with controlled open drain PIO pin. \nPIO pin sink capability is greater than 4mA at 0.4V.\n"},
            {0x06, "4096 bit read/write nonvolatile memory partitioned into \nsixteen pages of 256 bits each.\n"},
            {0x08, "1024 bit read/write nonvolatile memory partitioned \ninto four pages of 256 bits each.\n"},
            {0x09, "1024 bit Electrically Programmable Read Only \nMemory (EPROM) partitioned into four 256 bit pages.\n"},
            {0x0A, "16384 bit read/write nonvolatile memory \npartitioned into sixty-four pages of 256 bits each.\n"},
            {0x0B, "16384 bit Electrically Programmable Read Only \nMemory (EPROM) partitioned into sixty-four 256 bit pages.\n"},
            {0x0C, "65536 bit read/write nonvolatile memory \npartitioned into two-hundred fifty-six pages of 256 bits each.\n"},
            {0x0F, "65536 bit Electrically Programmable Read Only \nMemory (EPROM) partitioned into two-hundered fifty-six 256 bit pages.\n"},
            {0x10, "Digital thermometer from -55°C to 125°C \nwith 9 bit resolution.\n"},
            {0x12, "1-Wire Dual Addressable Switch. PIO pin channel A sink \ncapability of typical 50mA at 0.4V with soft turn-on.\n"},
            {0x13, "4096 bit Electrically Programmable Read Only Memory \n(EPROM) partitioned into sixteen 256 bit pages.\n"},
            {0x14, "Electrically Erasable Programmable Read Only Memory \n(EEPROM) organized as one page of 256 bits and 64 bit \none-time programmable application register.\n"},
            {0x18, "4096 bits of read/write nonvolatile memory. Memory is \npartitioned into sixteen pages of 256 bits each. \nHas overdrive mode.\n"},
            {0x1A, "4096 bit read/write nonvolatile memory with \nfour 32-bit read-only non rolling-over page write cycle \ncounters and tamper-detect bits for small money storage\n"},
            {0x1C, "Addressable 1-Wire 4K-bit EEPROM, with 2 channels of \ngeneral-purpose PIO pins with pulse generation capability.\n"},
            {0x1D, "1-Wire counter with 4096 bits of read/write, nonvolatile memory. \nMemory is partitioned into sixteen pages of 256 bits each.\n"},
            {0x1F, "1-Wire Network Coupler with dual addressable switches \nand a general purpose open drain control output.\n"},
            {0x20, "Four high-impedance inputs for measurement of analog voltages. \nUser programable input range. Very low power.\n"},
            {0x21, "Thermochron. Rugged, self-sufficient 1-Wire device that, once \nsetup for a mission, will measure the temperature and \nrecord the result in a protected memory section.\n"},
            {0x22, "Digital thermometer from -55°C to 125°C \nwith programmable resolution 9..12 bits.\n"},
            {0x23, "4096 bit Electrically Erasable Programmable Read Only Memory \n(EEPROM) organized as sixteen pages of 256 bits.\n"},
            {0x24, "Real time clock implemented as a binary counter.\n"},
            {0x26, "Smart Battery Monitor.\n"},
            {0x27, "Real time clock with interrupt implemented \nas a binary counter.\n"},
            {0x28, "Digital thermometer from -55°C to 125°C \nwith programmable resolution 9..12 bits.\n"},
            {0x29, "1-Wire 8-Channel Addressable Switch.\n"},
            {0x2C, "1-Wire linear taper digitally controlled \npotentiometer with 256 wiper positions. \n0-11 Volt working range.\n"},
            {0x2D, "1K-Bit protected 1-Wire EEPROM.\n"},
            {0x30, "1-Cell Li-Ion Battery Monitor.\n"},
            {0x33, "1K-Bit protected 1-Wire EEPROM \nwith SHA-1 Engine.\n"},
            {0x37, "Rugged, self-sufficient 1-Wire device that, once setup \ncan store 32KB of password protected memory \nwith a read only and a read/write password.\n"},
            {0x3A, "Dual Channel Addressable Switch.\n"},
            {0x41, "Hygrochron.\n"},
            {0x42, "Programmable resolution digital thermometer with 'sequence \ndetect' and 2 PIO channels. It measures temperature \nfrom -40°C to +85°C in 0.75 seconds (max).\n"},
            {0x43, "20Kb 1-Wire EEPROM.\n"},
            {0x55, "Pressure sensor DD84 with MDR32 MCU. Manufacturer ALCONT Ltd.\n"},
            {0x58, "Pressure sensor DD84 with GD32 MCU. Manufacturer ALCONT Ltd.\n"}
    };

    static inline QString deviceName;
    static inline QString descriptionString;
};

#endif // ONEWIRE_H
