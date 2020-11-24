#include "DS18B20.h"
#include <Arduino.h>

DS18B20::DS18B20(uint8_t DQ_Pin)
{
    this->DQ = DQ_Pin;
};
void DS18B20::WriteByte(uint8_t data)
{
    pinMode(this->DQ, OUTPUT);
    for (uint8_t i = 0; i < 8; i++)
    {
        digitalWrite(this->DQ, LOW);
        delayMicroseconds(5);
        digitalWrite(this->DQ, data & 0x01);
        delayMicroseconds(55);
        digitalWrite(this->DQ, HIGH);
        delayMicroseconds(1);
        data >>= 1;
    }
};
bool DS18B20::Init()
{
    pinMode(this->DQ, OUTPUT);
    digitalWrite(this->DQ, LOW);
    delayMicroseconds(500);
    digitalWrite(this->DQ, HIGH);
    pinMode(this->DQ, INPUT);
    delayMicroseconds(100);
    const bool result = !digitalRead(this->DQ);
    delayMicroseconds(400);
    return result;
};
uint8_t DS18B20::ReadByte()
{
    byte result;
    for (uint8_t i = 0; i < 8; i++)
    {
        result >>= 1;
        pinMode(this->DQ, OUTPUT);
        digitalWrite(this->DQ, LOW);
        delayMicroseconds(2);
        pinMode(this->DQ, INPUT);
        delayMicroseconds(8);
        if (digitalRead(this->DQ))
        {
            result |= 0x80;
        }
        delayMicroseconds(5);
        digitalWrite(this->DQ, HIGH);
        delayMicroseconds(1);
    }
    return result;
}
int DS18B20::GetTemperature()
{
    uint16_t data = 0;
    this->Init();
    this->WriteByte(0xcc);
    this->WriteByte(0x44);
    delay(55);
    this->Init();
    this->WriteByte(0xcc);
    this->WriteByte(0xbe);
    data |= this->ReadByte();
    data |= (this->ReadByte() << 8);
    data &= 0x7f8;
    data >>= 3;
    if (data & 0xf800)
    {
        return -data * 5;
    }
    return data * 5;
}