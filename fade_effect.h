#include "effect.h"

#ifndef FADE_EFFECT_H
#define FADE_EFFECT_H

class FadeEffect : public Effect
{
public:
    void init();
    static void duration(unsigned int);
    void update();
    char* name() const { return "fade"; }
    unsigned int maxDelay();
private:
    int stage;
    static unsigned short renderStep;
};

#endif // FADE_EFFECT_H
