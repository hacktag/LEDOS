#ifndef COLOREFFECT_H
#define COLOREFFECT_H

#include "effect.h"

/**
 * @brief The ColorEffect class creates a static color effect
 * @description Uses Active Color Space 1
 */
class ColorEffect : public Effect
{
public:
    void init();
    void update();
    char* name() const { return "color"; }
    unsigned int maxDelay();
};

#endif // COLOREFFECT_H
