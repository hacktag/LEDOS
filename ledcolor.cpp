#include "ledcolor.h"
#include "config.h"

struct LEDColorPrivate {
    byte R;
    byte G;
    byte B;
};

LEDColorPrivate *LEDColor::d_ptr = new LEDColorPrivate;

byte LEDColor::R()
{
    return d_ptr->R;
}

byte LEDColor::G()
{
    return d_ptr->G;
}

byte LEDColor::B()
{
    return d_ptr->B;
}

byte LEDColor::R(byte R)
{
    analogWrite(LED_R_PIN, R);
    return (d_ptr->R = R);
}

byte LEDColor::G(byte G)
{
    analogWrite(LED_G_PIN, G);
    return (d_ptr->G = G);
}

byte LEDColor::B(byte B)
{
    analogWrite(LED_B_PIN, B);
    return (d_ptr->B = B);
}
