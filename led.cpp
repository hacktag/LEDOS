#include "led.h"
#include "config.h"

struct LedPrivate {
    int R;
    int G;
    int B;
    int wR = PWMRANGE;
    int wG = PWMRANGE/2;
    int wB = PWMRANGE/3;
};

LedPrivate *Led::d_ptr = new LedPrivate;

int Led::R()
{
    return d_ptr->R;
}


int Led::G()
{
    return d_ptr->G;
}

int Led::B()
{
    return d_ptr->B;
}

int Led::R(byte R)
{
    d_ptr->R = R;    
    analogWrite(LED_R_PIN, constrain( (R * (d_ptr->wR + 1) / 255), 0, PWMRANGE));
    return R;
}

int Led::G(byte G)
{
    d_ptr->G = G;    
    analogWrite(LED_G_PIN, constrain( (G * (d_ptr->wG + 1) / 255), 0, PWMRANGE));
    return G;
}

int Led::B(byte B)
{
    d_ptr->B = B;    
    analogWrite(LED_B_PIN, constrain( (B * (d_ptr->wB + 1) / 255), 0, PWMRANGE));
    return B;
}

int Led::whiteR()
{
  return d_ptr->wR;
}

int Led::whiteG()
{
  return d_ptr->wG;
}

int Led::whiteB()
{
  return d_ptr->wB;
}

int Led::whiteR(int wR)
{
  return d_ptr->wR = constrain(wR, 0, PWMRANGE);
}

int Led::whiteG(int wG)
{
  return d_ptr->wG = constrain(wG, 0, PWMRANGE);
}

int Led::whiteB(int wB)
{
  return d_ptr->wB = constrain(wB, 0, PWMRANGE);
}

void Led::setWhiteValue(int wR, int wG, int wB)
{
  d_ptr->wR = wR;
  d_ptr->wG = wG;
  d_ptr->wB = wB;
}

void Led::setRGB(byte R, byte G, byte B)
{
    Led::R(R);
    Led::G(G);
    Led::B(B);
}

// Transforms colors defined in HSV to RGB
void Led::setHSV(float h, float s, float v)
{
  float f,p,q,t;
  int i;
  
  h = max(0.0, min(360.0, h));
  s = max(0.0, min(100.0, s));
  v = max(0.0, min(100.0, v));
  
  s /= 100;
  v /= 100;
  
  if(s == 0) {
    // Achromatic (grey)
    setRGB(round(v*255),round(v*255),round(v*255));
    return;
  }
 
  h /= 60; // sector 0 to 5
  i = floor(h);
  f = h - i; // factorial part of h
  p = v * (1 - s);
  q = v * (1 - s * f);
  t = v * (1 - s * (1 - f));
  switch(i) {
    case 0:
      R(round(255*v));
      G(round(255*t));
      B(round(255*p));
      break;
    case 1:
      R(round(255*q));
      G(round(255*v));
      B(round(255*p));
      break;
    case 2:
      R(round(255*p));
      G(round(255*v));
      B(round(255*t));
      break;
    case 3:
      R(round(255*p));
      G(round(255*q));
      B(round(255*v));
      break;
    case 4:
      R(round(255*t));
      G(round(255*p));
      B(round(255*v));
      break;
    default: // case 5:
      R(round(255*v));
      G(round(255*p));
      B(round(255*q));
    }
}
