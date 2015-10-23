#include "effect.h"

#ifndef HSV_FADE_EFFECT_H
#define HSV_FADE_EFFECT_H

class HSVFadeEffect : public Effect
{
public:
    void init();
    static void duration(unsigned int);
    void update();
    const char* name()  { return "HSV fade"; }
private:
    float stepSize, hue, sat, val;
    static unsigned short renderStep;
};

#endif // HSV_FADE_EFFECT_H
