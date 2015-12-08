#include "effect.h"

#ifndef HSI_FADE_EFFECT_H
#define HSI_FADE_EFFECT_H

class HSIFadeEffect : public Effect
{
public:
    void init();
    static void duration(unsigned int);
    void update();
    const char* name()  { return "HSI fade"; }
private:
    byte rgb[3];
    float hueStep, hue, sat, val;
    static unsigned short renderStep;
};

#endif // HSI_FADE_EFFECT_H
