#include "activecolor_effect.h"
#include <EEPROM.h>

struct ActiveColorEffectPrivate {
  byte R;
  byte G;
  byte B;
};

void ActiveColorEffect::init()
{
}

void ActiveColorEffect::update()
{
    stop(); // No need to constantly render the effect
}

void ActiveColorEffect::setColor( byte r, byte g, byte b ) {
  R(r);
  G(g);
  B(b);
}

unsigned int ActiveColorEffect::maxDelay()
{
    return -1;
}
