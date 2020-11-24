#pragma once
#include <Arduino.h>
#include "DS1302.h"
#include "DS18B20.h"
#include "AIP650.h"
class AtmegaClock
{
private:
    DS1302 *rtc;
    DS18B20 *tempreature_sensor;
    AIP650 *display;
    uint8_t display_values[4];
    uint8_t _display_values[4];
    Time current_time{2020, 1, 1, 0, 0, 0, Time::kSaturday};

    unsigned long current_mills;
    bool show_point;
    void DisplayData();
    void UpdateTime();

public:
    AtmegaClock(DS18B20 *temperature_sensor, DS1302 *rtc, AIP650 *display);
    void ShowTime();
    void ShowDate();
    void ShowYear();
    void ShowTemperature();
    void ShowAlarmClock();
    void Init();
};


