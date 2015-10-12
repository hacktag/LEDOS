#include "ledcolor.h"
#include "config.h"

struct LEDColorPrivate {
    byte R;
    byte G;
    byte B;
    float Rf;
    float Gf;
    float Bf;
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
    d_ptr->R = R * d_ptr->Rf;
    analogWrite(LED_R_PIN, d_ptr->R);
    return R;
}

byte LEDColor::G(byte G)
{
    d_ptr->G = G * d_ptr->Gf;
    analogWrite(LED_G_PIN, d_ptr->G);
    return G;
}

byte LEDColor::B(byte B)
{
    d_ptr->B = B * d_ptr->Bf;
    analogWrite(LED_B_PIN, d_ptr->B);
    return B;
}

float LEDColor::RFactor()
{
  return d_ptr->Rf;
}

float LEDColor::GFactor()
{
  return d_ptr->Gf;
}

float LEDColor::BFactor()
{
  return d_ptr->Bf;
}

float LEDColor::RFactor(float Rf)
{
  return d_ptr->Rf = Rf;
}

float LEDColor::GFactor(float Gf)
{
  return d_ptr->Gf = Gf;
}

float LEDColor::BFactor(float Bf)
{
  return d_ptr->Bf = Bf;
}
