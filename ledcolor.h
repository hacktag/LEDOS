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

private:
    static LEDColorPrivate *d_ptr;

    friend class SerialCLIController;
};

#endif // LED_COLOR_H
