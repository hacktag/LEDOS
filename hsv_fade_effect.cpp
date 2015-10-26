#include "hsv_fade_effect.h"

void HSVFadeEffect::init()
{
    stepSize = 0.1;
    hue = 0;
    sat = 100;
    val = m_brightness; 
    renderTime = millis();
}

void HSVFadeEffect::update()
{
    if( millis() < renderTime ) return;

    if (hue<=359.999-stepSize) hue += stepSize;
    else hue=0;

    setHSV(hue,sat,val);

    renderTime += ceil((float)m_duration / (3600));
}
