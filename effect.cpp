#include <Arduino.h>
#include "config.h"
#include "led.h"
#include "effect.h"

unsigned int Effect::m_duration = DEF_EFFECT_DURATION;
byte Effect::m_brightness = DEF_EFFECT_BRIGHTNESS;
unsigned long Effect::renderTime = 0;

void Effect::duration(unsigned int duration)
{
    m_duration = constrain(duration, 1, MAX_EFFECT_DURATION);
}

int Effect::duration()
{
    return m_duration;
}

void Effect::brightness(byte brightness)
{
    m_brightness =  constrain(brightness, 1, 255);
}

byte Effect::brightness()
{
    return m_brightness;
}

bool Effect::running()
{
    return m_running;
}

void Effect::start()
{
    m_running = true;
    init();
    Serial.print(name());
    Serial.println(" initialized");
    renderTime = millis();
}

void Effect::stop()
{
    m_running = false;
    Serial.print(name());
    Serial.println(" stopped");    
}

void Effect::reset()
{
    setRGB(0,0,0);
}
