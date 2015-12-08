#include "led.h"
#include "config.h"

struct LedPrivate {
    int R;
    int G;
    int B;
    int wR = DEF_MAX_RED;
    int wG = DEF_MAX_GREEN;
    int wB = DEF_MAX_BLUE;
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
  Led::whiteR(wR);
  Led::whiteG(wG);
  Led::whiteB(wB);
}

void Led::setRGB(byte R, byte G, byte B)
{
    Led::R(R);
    Led::G(G);
    Led::B(B);
}

void Led::setHSV(float h, float s, float v)
{
  byte rgb[3] = {0,0,0};
  Led::hsvToRgb(h, s, v, rgb);
  R(rgb[0]);
  G(rgb[1]);
  B(rgb[2]);
}

String Led::getWhiteValue() 
{
  return String(whiteR())+" "+String(whiteG())+" "+String(whiteB());
}

String Led::getRGB() 
{
  return String(R())+" "+String(G())+" "+String(B());
}


#include "math.h"

void Led::hsi2rgb(float H, float S, float I, byte rgb[]) {
  int r, g, b;
  H = 6.283185 * H; // Convert to radians
  if(H < 2.09439) {
    r = 255*I/3*(1+S*cos(H)/cos(1.047196667-H));
    g = 255*I/3*(1+S*(1-cos(H)/cos(1.047196667-H)));
    b = 255*I/3*(1-S);
  } else if(H < 4.188787) {
    H = H - 2.09439;
    g = 255*I/3*(1+S*cos(H)/cos(1.047196667-H));
    b = 255*I/3*(1+S*(1-cos(H)/cos(1.047196667-H)));
    r = 255*I/3*(1-S);
  } else {
    H = H - 4.188787;
    b = 255*I/3*(1+S*cos(H)/cos(1.047196667-H));
    r = 255*I/3*(1+S*(1-cos(H)/cos(1.047196667-H)));
    g = 255*I/3*(1-S);
  }
  rgb[0]=r;
  rgb[1]=g;
  rgb[2]=b;
}


/*
 * RGBConverter.h - Arduino library for converting between RGB, HSV and HSL
 * 
 * Ported from the Javascript at http://mjijackson.com/2008/02/rgb-to-hsl-and-rgb-to-hsv-color-model-conversion-algorithms-in-javascript
 * The hard work was Michael's, all the bugs are mine.
 *
 * Robert Atkins, December 2010 (ratkins_at_fastmail_dot_fm).
 *
 * https://github.com/ratkins/RGBConverter
 *
 */

/**
 * Converts an RGB color value to HSL. Conversion formula
 * adapted from http://en.wikipedia.org/wiki/HSL_color_space.
 * Assumes r, g, and b are contained in the set [0, 255] and
 * returns h, s, and l in the set [0, 1].
 *
 * @param   Number  r       The red color value
 * @param   Number  g       The green color value
 * @param   Number  b       The blue color value
 * @return  Array           The HSL representation
 */
void Led::rgbToHsl(byte r, byte g, byte b, double hsl[]) { 
    double rd = (double) r/255;
    double gd = (double) g/255;
    double bd = (double) b/255;
    double max = threeway_max(rd, gd, bd);
    double min = threeway_min(rd, gd, bd);
    double h, s, l = (max + min) / 2;

    if (max == min) {
        h = s = 0; // achromatic
    } else {
        double d = max - min;
        s = l > 0.5 ? d / (2 - max - min) : d / (max + min);
        if (max == rd) {
            h = (gd - bd) / d + (gd < bd ? 6 : 0);
        } else if (max == gd) {
            h = (bd - rd) / d + 2;
        } else if (max == bd) {
            h = (rd - gd) / d + 4;
        }
        h /= 6;
    }
    hsl[0] = h;
    hsl[1] = s;
    hsl[2] = l;
}

/**
 * Converts an HSL color value to RGB. Conversion formula
 * adapted from http://en.wikipedia.org/wiki/HSL_color_space.
 * Assumes h, s, and l are contained in the set [0, 1] and
 * returns r, g, and b in the set [0, 255].
 *
 * @param   Number  h       The hue
 * @param   Number  s       The saturation
 * @param   Number  l       The lightness
 * @return  Array           The RGB representation
 */
void Led::hslToRgb(double h, double s, double l, byte rgb[]) {
    double r, g, b;

    if (s == 0) {
        r = g = b = l; // achromatic
    } else {
        double q = l < 0.5 ? l * (1 + s) : l + s - l * s;
        double p = 2 * l - q;
        r = Led::hue2rgb(p, q, h + 1/3);
        g = Led::hue2rgb(p, q, h);
        b = Led::hue2rgb(p, q, h - 1/3);
    }

    rgb[0] = r * 255;
    rgb[1] = g * 255;
    rgb[2] = b * 255;
}

/**
 * Converts an RGB color value to HSV. Conversion formula
 * adapted from http://en.wikipedia.org/wiki/HSV_color_space.
 * Assumes r, g, and b are contained in the set [0, 255] and
 * returns h, s, and v in the set [0, 1].
 *
 * @param   Number  r       The red color value
 * @param   Number  g       The green color value
 * @param   Number  b       The blue color value
 * @return  Array           The HSV representation
 */
void Led::rgbToHsv(byte r, byte g, byte b, double hsv[]) {
    double rd = (double) r/255;
    double gd = (double) g/255;
    double bd = (double) b/255;
    double max = threeway_max(rd, gd, bd), min = threeway_min(rd, gd, bd);
    double h, s, v = max;

    double d = max - min;
    s = max == 0 ? 0 : d / max;

    if (max == min) { 
        h = 0; // achromatic
    } else {
        if (max == rd) {
            h = (gd - bd) / d + (gd < bd ? 6 : 0);
        } else if (max == gd) {
            h = (bd - rd) / d + 2;
        } else if (max == bd) {
            h = (rd - gd) / d + 4;
        }
        h /= 6;
    }

    hsv[0] = h;
    hsv[1] = s;
    hsv[2] = v;
}

/**
 * Converts an HSV color value to RGB. Conversion formula
 * adapted from http://en.wikipedia.org/wiki/HSV_color_space.
 * Assumes h, s, and v are contained in the set [0, 1] and
 * returns r, g, and b in the set [0, 255].
 *
 * @param   Number  h       The hue
 * @param   Number  s       The saturation
 * @param   Number  v       The value
 * @return  Array           The RGB representation
 */
void Led::hsvToRgb(double h, double s, double v, byte rgb[]) {
    double r, g, b;

    int i = int(h * 6);
    double f = h * 6 - i;
    double p = v * (1 - s);
    double q = v * (1 - f * s);
    double t = v * (1 - (1 - f) * s);

    switch(i % 6){
        case 0: r = v, g = t, b = p; break;
        case 1: r = q, g = v, b = p; break;
        case 2: r = p, g = v, b = t; break;
        case 3: r = p, g = q, b = v; break;
        case 4: r = t, g = p, b = v; break;
        case 5: r = v, g = p, b = q; break;
    }

    rgb[0] = r * 255;
    rgb[1] = g * 255;
    rgb[2] = b * 255;
}
 
double Led::threeway_max(double a, double b, double c) {
    return max(a, max(b, c));
}

double Led::threeway_min(double a, double b, double c) {
    return min(a, min(b, c));
}

double Led::hue2rgb(double p, double q, double t) {
    if(t < 0) t += 1;
    if(t > 1) t -= 1;
    if(t < 1/6) return p + (q - p) * 6 * t;
    if(t < 1/2) return q;
    if(t < 2/3) return p + (q - p) * (2/3 - t) * 6;
    return p;
}
