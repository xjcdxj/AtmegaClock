#pragma once
#define DQ_PIN 10
#define AIP_SCL 6
#define AIP_SDA 5
#define RTC_CE 9
#define RTC_IO 8
#define RTC_SCLK 7
#define LIGHT_SENSOR A7
#define IR 3
#define BEEPER 4
#define BUTTON_OK A5
#define BUTTON_SUB A4
#define BUTTON_ADD A3
#define BUTTON_SET A2
#define BUTTON_ALARM A1
#define BUTTON_SWITCH A0
#define TIME_MODE_ 0
#define DATE_MODE_ 1
#define YEAR_MODE_ 2
#define TEMPERATURE_MODE_ 3
#define ALARM_MODE_ 10

uint8_t BUTTON_LIST[6] = {BUTTON_OK, BUTTON_SWITCH, BUTTON_SET, BUTTON_ADD, BUTTON_SUB, BUTTON_ALARM};
typedef enum WorkingMode
{
    TIME_MODE,
    DATE_MODE,
    TEMPERATURE_MODE,
    ALARM_MODE

};