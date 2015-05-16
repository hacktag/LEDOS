#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "effect.h"

class Controller
{
public:
    Controller();
    virtual void init();
    virtual void update();

protected:
    static Effect *effects[];
    static Effect *currentEffect;
    static const int effectCount;
    static Controller *controllers[];
    static const int controllerCount;
};

#endif // CONTROLLER_H
