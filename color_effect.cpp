#include "color_effect.h"
#include <EEPROM.h>

void ColorEffect::init()
{
}

void ColorEffect::update()
{
    // Gets the colors from Active Color Space 1
    R( EEPROM.read(9) );
    G( EEPROM.read(10) );
    B( EEPROM.read(11) );
    stop(); // No need to constantly render the effect
}

unsigned int ColorEffect::maxDelay()
{
    return -1;
}
