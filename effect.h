#ifndef EFFECT_H
#define EFFECT_H

#include "ledcolor.h"

class EffectPrivate;

class Effect : public LEDColor {
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
     virtual char* name() const;

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
     * @brief Represents the maximum delay between update() calls.
     * @description Should be implemented by every effect.
     * @see update()
     */
    virtual unsigned int maxDelay();

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
    static unsigned long renderTime;

private:
    bool m_running;

    friend class Controller;
};

#endif
