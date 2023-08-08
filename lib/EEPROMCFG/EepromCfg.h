#include <Arduino.h>
#include <EEPROM.h>

#ifndef EEPROMCFG_H
#define EEPROMCFG_H

#define EEPROMSIZE 512


//TODO TERMINAR ESTA CLASE IPLEMENTANDO LECTURA DE PARÁMETROS
#define LOWTEMPSTART 0 //5chars 
#define HIGHTEMPSTART 5



class EEPROMCFG
{
private:
    static void writeString(uint8_t address, const char *str);
    static void readString(uint8_t address, uint8_t maxLen, char *str);

public:
    static void saveLowTemp(const char *str);
    static void readLowTemp(char *str);
};
void EEPROMCFG::saveLowTemp(const char *str)
{
    writeString(LOWTEMPSTART, str);
}

void EEPROMCFG::readLowTemp(char *str)
{
    readString(LOWTEMPSTART, 10, str);
}

void EEPROMCFG::writeString(uint8_t address, const char *str)
{
    uint8_t len = (str == nullptr ? 0 : strlen(str));
    uint8_t i = 0;
    while(i <= len) {
        EEPROM.write(address + i, str[i]);
        i++;
    }
}

void EEPROMCFG::readString(uint8_t address, uint8_t maxLen, char *str)
{
    str[0] = 0;
    uint8_t lastChar = 0;
    uint8_t i = 0;
    do
    {
        lastChar = EEPROM.read(address + i);
        str[i] = char(lastChar);
        i++;
    } while (lastChar != 0 && i < maxLen);
    if (lastChar != 0 && i >= maxLen)
    {
        str[0] = 0;
    }
}

#endif
