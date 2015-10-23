#ifndef EFFECT_H
#define EFFECT_H

#include "led.h"

class EffectPrivate;

class Effect : public Led {
public:

//    /**
//     * @brief Effect constructor
//     * @description Always call the Effect constructor when subclassing from it
//     */
//    Effect();

//    /**
//     * @brief Effect destructor
//     */
//    ~Effect();

     /**
      * @brief Specifies Effect Name
      */
     virtual const char* name() ;

    /**
     * @brief This method is called upon effect initialisation
     */
    virtual void init();

    /**
     * @brief This method is called on each frame update
     */
    virtual void update();

    /**
     * @brief Defines the duration o
     */
    static void duration(unsigned int);

    /**
     * @brief Gets the duration of an effect
     */
    static int duration();
    
    /**
     * @brief Sets the brighness of the effect
     */
    static void brightness(byte);

    /**
     * @brief Gets the brightness of an effect
     */
    static byte brightness();

    /**
     * @brief Gets the effect current state
     */
    bool running();

    /**
     * @brief Starts the effect
     */
    virtual void start();

    /**
     * @brief Stops the effect
     */
    virtual void stop();

    /**
     * @brief Turns the LED strip off
     */
    void reset();

protected:
    static unsigned int m_duration;
    static byte m_brightness;
    static unsigned long renderTime;

private:
    bool m_running;
};

#endif
