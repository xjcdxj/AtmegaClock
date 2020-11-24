#pragma once
#include <Arduino.h>
static uint8_t display_num[10] = {
    0x3f,
    0x06,
    0x5b,
    0x4f,
    0x66,
    0x6d,
    0x7d,
    0x07,
    0x7f,
    0x6f};
class AIP650
{
private:
    uint8_t SCL;
    uint8_t SDA;
    void Start();
    void Stop();
    bool Ack();
    void WriteData(uint16_t data);
    uint8_t display_cache[4];

public:
    AIP650(uint8_t SCL, uint8_t SDA);
    void DisplayNumByIndex(uint8_t num, bool point, uint8_t index);
    void DisplayByIndex(uint8_t index, uint8_t vlaue);
    void SetBrightness(uint8_t brightness);
    void Init();
    void ShutDown();
    void SleepMode();
    void WriteData(uint8_t h_data, uint8_t l_data);
    void DisplayNum(uint16_t num);
    void Display(uint8_t *data_array);

    void test();
};
