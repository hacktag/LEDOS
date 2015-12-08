#include "hsi_fade_effect.h"

void HSIFadeEffect::init()
{
    hueStep = 0.001;
    hue = 0;
    sat = 1;
    val = (double) m_brightness/255; 
    renderTime = millis();
}

void HSIFadeEffect::update()
{
    if( millis() < renderTime ) return;

    if (hue<=1-hueStep) hue += hueStep;
    else hue=0;

    hsi2rgb(hue,sat,(float) m_brightness/255,rgb);
    setRGB(rgb[0],rgb[1],rgb[2]);

//    Serial.println(getRGB());
    
    renderTime += ceil((float)m_duration*hueStep);
}
