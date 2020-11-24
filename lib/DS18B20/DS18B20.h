#ifndef __DS18B20__H_
#define __DS18B20__H_
#include <Arduino.h>

class DS18B20
{
private:
    /* data */
    void WriteByte(uint8_t data);
    bool Init();
    uint8_t ReadByte();
    uint8_t DQ;

public:
    DS18B20(uint8_t DQ_Pin);
     int GetTemperature();
};
#endif