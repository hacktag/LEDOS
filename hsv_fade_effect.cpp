//#include "hsv_fade_effect.h"
//
//void HSVFadeEffect::init()
//{
//    stepSize = 0.1;
//    hue = 0;
//    sat = 100;
//    val = m_brightness
//    renderTime = millis();
//}
//
//void HSVFadeEffect::update()
//{
//    if( millis() < renderTime ) return;
//
//    if (color_value_hsv[active_color]<=359.999-stepSizeHSV) color_value_hsv[active_color] += stepSizeHSV;
//    else color_value_hsv[active_color]=0;
//
//    setHSV(hue,sat,val);
//
//    renderTime += ceil((float)m_duration / (m_brightness*6));
//}
