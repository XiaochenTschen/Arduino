#ifndef _ENCODER_KY400_H
#define _ENCODER_KY400_H

#include <Arduino.h>

class Encoder_KY400 
{
public:
    Encoder_KY400(uint8_t clk, uint8_t dt, uint8_t sw, int upper_limit, int low_limit):
        _clk(clk), _dt(dt), _sw(sw), _upper_limit(upper_limit), _low_limit(low_limit)
    {
        pinMode(_clk, INPUT);
        pinMode(_dt, INPUT);
        pinMode(_sw, INPUT_PULLUP);

        instance = this;

        attachInterrupt(_clk, Encoder_KY400::cLK_ISR, RISING);
        attachInterrupt(_sw, Encoder_KY400::btn_ISR, FALLING);
    }
    ~Encoder_KY400(){}

    bool clkw;
    int counter = 0;

    void reg_btnCallback(void (*fp)(void))
    {
        _btnCallback = fp;
    }

    static void cLK_ISR()
    {
        if(instance != nullptr)
        {
            instance->cLK_ISR_Handler();
        }
    }

    static void btn_ISR()
    {
        if(instance != nullptr)
        {
            instance->btn_ISR_Handler();
        }
    }

private:
    uint8_t _clk, _dt, _sw;
    int _upper_limit, _low_limit;
    unsigned long _lastPush = 0;
    void (*_btnCallback)(void) = nullptr;

    static Encoder_KY400* instance = nullptr;

    void cLK_ISR_Handler()
    {
        if(digitalRead(ENCODER_DT) == LOW)
        {
            clkw = true;
            if(++counter > _upper_limit) counter = _upper_limit;
        }
        else
        {
            clkw = false;
            if(--counter < _low_limit) counter = _low_limit;
        }
        Serial.print("counter: "); Serial.println(counter);
    }

    void btn_ISR_Handler()
    {
        if(millis() - _lastPush < 500)
        {
            return;
        }
        _lastPush = millis();
        if(_btnCallback != nullptr)
        {
             _btnCallback();
        }
    }
};

#endif

