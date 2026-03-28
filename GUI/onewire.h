#ifndef ONEWIRE_H
#define ONEWIRE_H

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
    static const inline QMap<quint8, QString> deviceMap =
    {
        {0x01, "DS1990A"},  // 64-bit unique serial number
        {0x02, "DS1991"},   // 2048 bits of nonvolatile read/write memory
        {0x04, "DS1994"},   // 4096 bit read/write nonvolatile memory
        {0x05, "DS2405"},   // Addressable Switch with controlled open drain PIO pin
        {0x06, "DS1993"},   // 4096 bit read/write nonvolatile memory
        {0x08, "DS1992"},   // 1024 bit read/write nonvolatile memory
        {0x09, "DS1982"},   // 1024 bit Electrically Programmable Read Only Memory
        {0x0A, "DS1995"},   // 16384 bit read/write nonvolatile memory
        {0x0B, "DS1985"},   // 16384 bit Electrically Programmable Read Only Memory
        {0x0C, "DS1996"},   // 65536 bit read/write nonvolatile memory
        {0x0F, "DS1986"},   // 65536 bit Electrically Programmable Read Only Memory
        {0x10, "DS18S20"},  // Digital thermometer -55C to 125C 9 bit resolution
        {0x12, "DS2406"},   // 1-Wire Dual Addressable Switch
        {0x13, "DS1983"},   // 4096 bit Electrically Programmable Read Only Memory
        {0x14, "DS1971"},   // Electrically Erasable Programmable Read Only Memory
        {0x18, "DS1963S"},  // 4096 bits of read/write nonvolatile memory
        {0x1A, "DS1963L"},  // 4096 bit read/write nonvolatile memory
        {0x1C, "DS28E04"},  // Addressable 1-Wire 4K-bit EEPROM
        {0x1D, "DS2423"},   // 1-Wire counter with 4096 bits of read/write
        {0x1F, "DS2409"},   // 1-Wire Network Coupler with dual addressable
        {0x20, "DS2450"},   // Four high-impedance inputs for measurement of analog voltages
        {0x21, "DS1921"},   // Thermochron
        {0x22, "DS1822"},   // Digital thermometer -55C to 125C 12 bit resolution
        {0x23, "DS1973"},   // EEPROM 4096 bits
        {0x24, "DS2415"},   // Real time clock
        {0x26, "DS2438"},   // Smart Battery Monitor
        {0x27, "DS2417"},   // Real time clock with interrupt
        {0x28, "DS18B20"},  // Digital thermometer -55C to 125C 12 bit resolution
        {0x29, "DS2408"},   // 1-Wire 8-Channel Addressable Switch
        {0x2C, "DS2890"},   // 1-Wire linear taper digitally controlled potentiometer with 256 wiper positions
        {0x2D, "DS1972"},   // 1K-Bit protected 1-Wire EEPROM
        {0x30, "DS2760"},   // 1-Cell Li-Ion Battery Monitor
        {0x33, "DS1961S"},  // 1K-Bit protected 1-Wire EEPROM with SHA-1 Engine
        {0x37, "DS1977"},   // 32KB password protected memory
        {0x3A, "DS2413"},   // Dual Channel Addressable Switch
        {0x41, "DS1923"},   // Hygrochron
        {0x42, "DS28EA00"}, // Programmable resolution digital thermometer with 'sequence detect'
        {0x43, "DS28EC20"},  // 20Kb 1-Wire EEPROM
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
    };

    static inline QString deviceName;
    static inline QString descriptionString;
};

#endif // ONEWIRE_H
