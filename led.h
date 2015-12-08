#ifndef LED_H
#define LED_H

#include <Arduino.h>

class LedPrivate;

class Led
{
public:
    /**
     * @brief Returns the current 10 bit value of the Red color
     */
     static int R();

    /**
     * @brief Returns the current 10 bit value of the Green color
     */
     static int G();

    /**
     * @brief Returns the current 10 bit value of the Blue color
     */
     static int B();

     /**
      * @brief Returns the current scaling factor of the Red color
      */
      static int whiteR();

     /**
      * @brief Returns the current scaling factor of the Green color
      */
      static int whiteG();

     /**
      * @brief Returns the current scaling factor of the Blue color
      */
      static int whiteB();

    /**
     * @brief Returns the current value of the Red color
     */
     static int R(byte);

    /**
     * @brief Returns the current value of the Green color
     */
     static int G(byte);

    /**
     * @brief Returns the current value of the Blue color
     */
     static int B(byte);

     /**
      * @brief Sets the max level of the Red color
      */
      static int whiteR(int);

     /**
      * @brief Sets the max level of the Green color
      */
      static int whiteG(int);

     /**
      * @brief Sets the max level of the Blue color
      */
      static int whiteB(int);

      static void setWhiteValue(int Rf, int Gf, int Bf);

      static void setRGB(byte R, byte G, byte B);

      static void setHSV(float H, float S, float V);
      static void setHSVre(float H, float S, float V);

      static String getWhiteValue();
      static String getRGB();

      static void hsi2rgb(float H, float S, float I, byte rgb[]);
      
      /**
       * Converts an RGB color value to HSL. Conversion formula
       * adapted from http://en.wikipedia.org/wiki/HSL_color_space.
       * Assumes r, g, and b are contained in the set [0, 255] and
       * returns h, s, and l in the set [0, 1].
       *
       * @param   byte    r       The red color value
       * @param   byte    g       The green color value
       * @param   byte    b       The blue color value
       * @param   double  hsl[]   The HSL representation
       */
      static void rgbToHsl(byte r, byte g, byte b, double hsl[]);
      
      /**
       * Converts an HSL color value to RGB. Conversion formula
       * adapted from http://en.wikipedia.org/wiki/HSL_color_space.
       * Assumes h, s, and l are contained in the set [0, 1] and
       * returns r, g, and b in the set [0, 255].
       *
       * @param   double  h       The hue
       * @param   double  s       The saturation
       * @param   double  l       The lightness
       * @return  byte    rgb[]   The RGB representation
       */
      static void hslToRgb(double h, double s, double l, byte rgb[]);
  
      /**
       * Converts an RGB color value to HSV. Conversion formula
       * adapted from http://en.wikipedia.org/wiki/HSV_color_space.
       * Assumes r, g, and b are contained in the set [0, 255] and
       * returns h, s, and v in the set [0, 1].
       *
       * @param   byte  r       The red color value
       * @param   byte  g       The green color value
       * @param   byte  b       The blue color value
       * @return  double hsv[]  The HSV representation
       */
      static void rgbToHsv(byte r, byte g, byte b, double hsv[]);
      
      /**
       * Converts an HSV color value to RGB. Conversion formula
       * adapted from http://en.wikipedia.org/wiki/HSV_color_space.
       * Assumes h, s, and v are contained in the set [0, 1] and
       * returns r, g, and b in the set [0, 255].
       *
       * @param   double  h       The hue
       * @param   double  s       The saturation
       * @param   double  v       The value
       * @return  byte    rgb[]   The RGB representation
       */
      static void hsvToRgb(double h, double s, double v, byte rgb[]);

private:
    static LedPrivate *d_ptr;
    static double threeway_max(double a, double b, double c);
    static double threeway_min(double a, double b, double c);
    static double hue2rgb(double p, double q, double t);
};

#endif // LED_H
