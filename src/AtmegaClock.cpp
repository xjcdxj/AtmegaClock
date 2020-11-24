#include "AtmegaClock.h"

bool ShowPoint()
{
    return millis() >> 9 & 0x01;
}
void AtmegaClock::ShowTime()
{
    this->UpdateTime();
    this->show_point = millis() >> 9 & 0x01;
    this->display_values[0] = display_num[current_time.hr / 10];
    this->display_values[1] = display_num[current_time.hr % 10] | (show_point << 7);
    this->display_values[2] = display_num[current_time.min / 10] | (show_point << 7);
    this->display_values[3] = display_num[current_time.min % 10];

    this->DisplayData();
}

void AtmegaClock::DisplayData()
{
    this->display->Display(this->display_values);
    // this->display->DisplayByIndex(0, this->display_values[0]);
    // this->display->DisplayByIndex(1, this->display_values[1]);
    // this->display->DisplayByIndex(2, this->display_values[2]);
    // this->display->DisplayByIndex(3, this->display_values[3]);
}
AtmegaClock::AtmegaClock(DS18B20 *temperature_sensor, DS1302 *rtc, AIP650 *display)
{
    this->rtc = rtc;
    this->tempreature_sensor = temperature_sensor;
    this->display = display;
}
void AtmegaClock::UpdateTime()
{
    if (millis() - this->current_mills > 59990)
    {
        /* code */
        this->current_time = this->rtc->time();

        if (this->current_time.sec == 0)
        {
            /* code */
            this->current_mills = millis();
        }
    }
}
void AtmegaClock::Init()
{
    this->rtc->halt(false);
    this->rtc->writeProtect(true);
    this->display->Init();
    this->current_time = this->rtc->time();
    this->current_mills = millis() - this->current_time.sec * 1000 - 1000;
}

void AtmegaClock::ShowDate()
{
    this->UpdateTime();
    this->display_values[0] = display_num[this->current_time.mon / 10];
    this->display_values[1] = display_num[this->current_time.mon % 10] | 0x80;
    this->display_values[2] = display_num[this->current_time.date / 10];
    this->display_values[3] = display_num[this->current_time.date % 10];
    this->DisplayData();
}
void AtmegaClock::ShowYear()
{
    this->UpdateTime();
    this->display_values[0] = display_num[this->current_time.yr / 1000];
    this->display_values[1] = display_num[this->current_time.yr / 100 % 10];
    this->display_values[2] = display_num[this->current_time.yr / 10 % 10];
    this->display_values[3] = display_num[this->current_time.yr % 10];
    this->DisplayData();
}
void AtmegaClock::ShowTemperature()
{
    int temperature = this->tempreature_sensor->GetTemperature();
    if (temperature > 0)
    {
        /* code */
        this->display_values[0] = display_num[temperature / 100 % 10];
        this->display_values[1] = display_num[temperature / 10 % 10] | 0x80;
        this->display_values[2] = display_num[temperature % 10];
    }
    else
    {
        /* code */
        this->display_values[0] = 0x40;
        this->display_values[1] = display_num[abs(temperature) / 100 % 10];
        this->display_values[2] = display_num[abs(temperature) / 10 % 10];
    }

    this->display_values[3] = 0xe1;
    this->DisplayData();
}
void AtmegaClock::ShowAlarmClock() {}