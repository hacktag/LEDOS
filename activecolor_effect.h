#ifndef ACTIVECOLOREFFECT_H
#define ACTIVECOLOREFFECT_H

#include "effect.h"

struct ActiveColorEffectPrivate;

/**
 * @brief The ColorEffect class creates a static color effect
 * @description Uses Active Color Space 1
 */
class ActiveColorEffect : public Effect
{
public:
    void init();
    void update();
    void setColor( byte, byte, byte );
    char* name() const { return "activecolor"; }
    unsigned int maxDelay();

private:
  ActiveColorEffectPrivate *d_ptr;
};

#endif // ACTIVECOLOREFFECT_H
