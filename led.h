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

private:
    static LedPrivate *d_ptr;
};

#endif // LED_H
