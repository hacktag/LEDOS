#include "effect.h"

#ifndef RGB_FADE_EFFECT_H
#define RGB_FADE_EFFECT_H

class RGBFadeEffect : public Effect
{
public:
    void init();
    static void duration(unsigned int);
    void update();
    const char* name()  { return "RGB fade"; }
private:
    int stage;
    static unsigned short renderStep;
};

#endif // RGB_FADE_EFFECT_H
