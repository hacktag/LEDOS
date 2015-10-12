#ifndef LED_COLOR_H
#define LED_COLOR_H

#include <Arduino.h>

class LEDColorPrivate;

class LEDColor
{
public:
    /**
     * @brief Returns the current value of the Red color
     */
     static byte R();

    /**
     * @brief Returns the current value of the Green color
     */
     static byte G();

    /**
     * @brief Returns the current value of the Blue color
     */
     static byte B();

     /**
      * @brief Returns the current scaling factor of the Red color
      */
      static float RFactor();

     /**
      * @brief Returns the current scaling factor of the Green color
      */
      static float GFactor();

     /**
      * @brief Returns the current scaling factor of the Blue color
      */
      static float BFactor();

protected:

    /**
     * @brief Returns the current value of the Red color
     */
     static byte R(byte);

    /**
     * @brief Returns the current value of the Green color
     */
     static byte G(byte);

    /**
     * @brief Returns the current value of the Blue color
     */
     static byte B(byte);

     /**
      * @brief Sets the current scaling factor of the Red color
      */
      static float RFactor(float);

     /**
      * @brief Sets the current scaling factor of the Green color
      */
      static float GFactor(float);

     /**
      * @brief Sets the current scaling factor of the Blue color
      */
      static float BFactor(float);

private:
    static LEDColorPrivate *d_ptr;

    friend class SerialCLIController;
};

#endif // LED_COLOR_H
