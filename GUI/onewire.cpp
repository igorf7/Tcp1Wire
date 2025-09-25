#include "onewire.h"

/**
 * @brief OneWire::getName
 * @param family
 * @return
 */

QString& OneWire::getName(quint8 family)
{
    return deviceName = deviceMap.key(family);
}

/**
 * @brief OneWire::getDescription
 * @param family
 * @return
 */
QString& OneWire::getDescription(quint8 family)
{
    return descriptionString = description.value(family);
}

/**
 * @brief OneWire::getFamily
 * @param name
 * @return
 */
quint8 OneWire::getFamily(const QString &name)
{
    return deviceMap.value(name);
}

/**
 * @brief OneWire::calcCrc8
 * @param data
 * @param size
 * @return
 */
quint8 OneWire::calcCrc8(quint8 *data, quint16 size)
{
    quint8 crc = 0;

    for (quint16 i = 0; i < size; ++i ) {
        quint8 inbyte = data[i];
        for (quint8 j = 0; j < 8; ++j ) {
            quint8 mix = (crc ^ inbyte) & 0x01;
            crc >>= 1;
            if ( mix ) crc ^= 0x8C;
            inbyte >>= 1;
        }
    }
    return crc;
}
