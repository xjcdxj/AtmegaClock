#include <Arduino.h>
#include "ClockConfig.h"
#include "DS18B20.h"
#include "DS1302.h"
#include "AIP650.h"
#include "AtmegaClock.h"
DS18B20 ds18b20(DQ_PIN);
DS1302 ds1302(RTC_CE, RTC_IO, RTC_SCLK);
AIP650 aip650(AIP_SCL, AIP_SDA);
AtmegaClock atmegaClock(&ds18b20, &ds1302, &aip650);

int8_t brightness = 0;
uint8_t working_mode = 0;
void ProgramStart()
{
    uint8_t temp_ = 1;
    for (uint8_t j = 0; j < 6; j++)
    {
        /* code */
        for (uint8_t i = 0; i < 4; i++)
        {

            aip650.DisplayByIndex(i, temp_);
                }
        delay(200);
        temp_ = (temp_ << 1) | 0x01;
    }
}
void setup()

{
    atmegaClock.Init();
    Serial.begin(256000);
    ProgramStart();
}
uint8_t GetPressedButton()
{
    for (uint8_t index = 0; index < 6; index++)
    {
        if (!digitalRead(BUTTON_LIST[index]))
        {
            delay(10);
            if (!digitalRead(BUTTON_LIST[index]))
            {
                while (!digitalRead(BUTTON_LIST[index]))
                {
                    /* code */
                }
                return BUTTON_LIST[index];
            }
        }
    }
    return 0;
}
void working()
{
    switch (GetPressedButton())
    {
    case BUTTON_SWITCH:
        /* code */
        working_mode += 1;
        if (working_mode > TEMPERATURE_MODE_)
        {
            working_mode = 0;
        }
        break;
    case BUTTON_ADD:
        brightness += 1;
        if (brightness > 7)
        {
            /* code */
            brightness = 0;
        }

        aip650.SetBrightness(brightness);
        break;
    case BUTTON_SUB:
        brightness -= 1;
        if (brightness < 0)
        {
            /* code */
            brightness = 7;
        }
        aip650.SetBrightness(brightness);
        break;
    default:
        break;
    }
    switch (working_mode)
    {
    case TIME_MODE_:
        atmegaClock.ShowTime();
        break;
    case DATE_MODE_:
        atmegaClock.ShowDate();
        break;
    case YEAR_MODE_:
        atmegaClock.ShowYear();
        break;
    case TEMPERATURE_MODE_:
        atmegaClock.ShowTemperature();
        break;
    case ALARM_MODE_:
        atmegaClock.ShowAlarmClock();
        break;
    default:
        break;
    }
}
uint8_t mode = WorkingMode::TIME_MODE;
void loop()
{
    working();
}