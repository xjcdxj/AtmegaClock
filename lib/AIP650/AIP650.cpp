#include "AIP650.h"

void AIP650::Start()
{
    pinMode(this->SCL, OUTPUT);
    pinMode(this->SDA, OUTPUT);
    digitalWrite(this->SDA, 1);
    digitalWrite(this->SCL, 1);
    digitalWrite(this->SDA, 0);
}
void AIP650::Stop()
{
    pinMode(this->SCL, OUTPUT);
    pinMode(this->SDA, OUTPUT);
    digitalWrite(this->SDA, 0);
    digitalWrite(this->SCL, 1);
    digitalWrite(this->SDA, 1);
}
bool AIP650::Ack()
{
    digitalWrite(this->SCL, 0);
    pinMode(SDA, INPUT);
    digitalWrite(this->SCL, 1);
    while (digitalRead(SDA))
    {
    }
    digitalWrite(this->SCL, 0);
    pinMode(this->SDA, OUTPUT);
    return true;
}
void AIP650::WriteData(uint8_t h_data, uint8_t l_data)
{
    this->Start();
    uint8_t temp = 0x80;
    pinMode(this->SCL, OUTPUT);
    pinMode(this->SDA, OUTPUT);
    while (temp)
    {
        digitalWrite(this->SCL, 0);
        digitalWrite(this->SDA, temp & h_data);
        digitalWrite(this->SCL, 1);
        temp >>= 1;
    }
    this->Ack();
    temp = 0x80;
    while (temp)
    {
        digitalWrite(this->SCL, 0);
        digitalWrite(this->SDA, temp & l_data);
        digitalWrite(this->SCL, 1);
        temp >>= 1;
    }
    this->Ack();
    this->Stop();
}
void AIP650::WriteData(uint16_t data)
{
    pinMode(this->SCL, OUTPUT);
    pinMode(this->SDA, OUTPUT);
    this->Start();
    uint16_t TempData = 0x8000;
    while (TempData)
    {
        digitalWrite(this->SCL, 0);
        digitalWrite(this->SDA, (!((TempData & data) == 0)));
        digitalWrite(this->SCL, 1);
        TempData >>= 1;
        if (TempData == 0x80)
        {
            this->Ack();
        }
    }
    this->Ack();
    this->Stop();
}
void AIP650::test()
{
    // this->WriteData(0x48, 0x01);
    // this->WriteData(0x68, 0xff);
    // this->WriteData(0x6a, 0xff);
    // this->WriteData(0x6c, 0xff);
    // this->WriteData(0x6e, 0xff);
    this->DisplayNumByIndex(1, true, 2);
    for (uint8_t i = 0; i < 9; i++)
    {
        this->SetBrightness(i);
        delay(500);
    }
    this->SleepMode();
    delay(500);
    this->SetBrightness(1);
    delay(500);
}
AIP650::AIP650(uint8_t SCL, uint8_t SDA)

{
    this->SCL = SCL;
    this->SDA = SDA;
}
void AIP650::DisplayNumByIndex(uint8_t num, bool point, uint8_t index)
{
    this->WriteData(0x68 + 2 * index, display_num[num] | (point << 7));
}
void AIP650::DisplayByIndex(uint8_t index, uint8_t vlaue)
{
    this->WriteData(0x68 + 2 * index, vlaue);
}

void AIP650::SetBrightness(uint8_t brightness)
{
    this->WriteData(0x48, (brightness << 4) | 1);
}
void AIP650::SleepMode()
{
    this->WriteData(0x48, 0x04);
}
void AIP650::ShutDown()
{
    this->WriteData(0x48, 0x00);
}
void AIP650::Init()
{
    this->WriteData(0x48, 0x01);
    this->WriteData(0x68, 0);
    this->WriteData(0x6a, 0);
    this->WriteData(0x6c, 0);
    this->WriteData(0x6e, 0);
}

void AIP650::DisplayNum(uint16_t num)
{

    this->DisplayByIndex(0, display_num[num / 1000 % 10]);
    this->DisplayByIndex(1, display_num[num % 1000 / 100]);
    this->DisplayByIndex(2, display_num[num % 100 / 10]);
    this->DisplayByIndex(3, display_num[num % 10]);
}

void AIP650::Display(uint8_t *data_array)
{
    for (uint8_t i = 0; i < 4; i++)
    {
        if (data_array[i] != this->display_cache[i])
        {
            this->display_cache[i] = data_array[i];
            this->DisplayByIndex(i, data_array[i]);
        }
    }
}