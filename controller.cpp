#include "controller.h"

#include "rgb_fade_effect.h"
#include "serial_cli_controller.h"

Effect *Controller::effects[] = { new RGBFadeEffect() };
const int Controller::effectCount = sizeof(Controller::effects) / sizeof(Effect*);
Effect *Controller::currentEffect;

Controller *Controller::controllers[] = { new SerialCLIController() };
const int Controller::controllerCount = sizeof(Controller::controllers) / sizeof(Controller*);

int lastMode = 0;
int mode = 0;

Controller::Controller()
{
}

void Controller::init()
{
    for(int i = 0; i < controllerCount; ++i)
    {
        controllers[i]->init();
    }
    
    if( mode > -1 ) // LED OFF
    {
        currentEffect = effects[mode];
        currentEffect->init();
        currentEffect->start();
    }
}

void Controller::update()
{
    for(int i = 0; i < controllerCount; ++i)
    {
        controllers[i]->update();
    }

    if(currentEffect->running())
        currentEffect->update();
}
