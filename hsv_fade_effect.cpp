#include "hsv_fade_effect.h"

void HSVFadeEffect::init()
{
    hsvStep = 0.1;
    satStep = 0.0001;
    hue = 0;
    sat = 100;
    val = m_brightness; 
    renderTime = millis();
}

void HSVFadeEffect::update()
{
    if( millis() < renderTime ) return;

    if (hue<=359.999-hsvStep) hue += hsvStep;
    else hue=0;
    if (sat<80 || sat>100) satStep=-satStep;
    sat -= satStep;

    setHSV(hue,sat,m_brightness);

    renderTime += ceil((float)m_duration / (3600));
}
