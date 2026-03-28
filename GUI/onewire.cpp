#include "onewire.h"

/**
 * @brief OneWire::getName
 * @param family
 * @return
 */

QString& OneWire::getName(quint8 family)
{
    if (deviceMap.contains(family))
        return deviceName = deviceMap.value(family);
    else
        return deviceName = "0x" + QString::number(family, 16).toUpper();
}

/**
 * @brief OneWire::getDescription
 * @param family
 * @return
 */
QString& OneWire::getDescription(quint8 family)
{
    if (description.contains(family))
        return descriptionString = description.value(family);
    else
        return descriptionString = "Unknoun device with family code 0x" +
                                   QString::number(family, 16).toUpper();
}

/**
 * @brief OneWire::getFamily
 * @param name
 * @return
 */
quint8 OneWire::getFamily(const QString &name)
{
    quint8 family = deviceMap.key(name, 0);

    if (family != 0) {
        return family;
    }
    else {
        bool Ok;
        quint8 val = (quint8)name.toUInt(&Ok, 16);
        family = Ok ? val : 0;
    }
    return family;
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
