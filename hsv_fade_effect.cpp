#include "hsv_fade_effect.h"

void HSVFadeEffect::init()
{
    hueStep = 0.001;
    hue = 0;
    sat = 1;
    val = (double) m_brightness/255; 
    renderTime = millis();
}

void HSVFadeEffect::update()
{
    if( millis() < renderTime ) return;

    if (hue<=1-hueStep) hue += hueStep;
    else hue=0;

    setHSV(hue,sat,(float) m_brightness/255);
    
//    Serial.println(getRGB());

    renderTime += ceil((float)m_duration*hueStep);
}
