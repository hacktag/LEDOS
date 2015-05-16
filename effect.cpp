#include "effect.h"
#include <Arduino.h>
#include <EEPROM.h>
#include "config.h"

unsigned int Effect::m_duration = 10000;
unsigned long Effect::renderTime = 0;

void Effect::duration(unsigned int duration)
{
    m_duration = duration;
    EEPROM.put(3, duration);
}

int Effect::duration()
{
    return m_duration;
}

bool Effect::running()
{
    return m_running;
}

void Effect::start()
{
    m_running = true;
    renderTime = millis();
}

void Effect::stop()
{
    m_running = false;
}

void Effect::reset()
{
    R(0);
    G(0);
    B(0);
}
