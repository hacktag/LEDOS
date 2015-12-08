#include "effect.h"

#ifndef RANDOM_FADE_EFFECT_H
#define RANDOM_FADE_EFFECT_H

class RandomFadeEffect : public Effect
{
public:
    void init();
    static void duration(unsigned int);
    void update();
    const char* name()  { return "random fade"; }
    void pickRandomColor();
private:
    float hue, sat, val;
    byte rgbStep;
    byte rgb[3];
    int distance;
};

#endif // RANDOM_FADE_EFFECT_H
