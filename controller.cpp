#include <EEPROM.h>
#include "controller.h"
#include "color_effect.h"
#include "fade_effect.h"
#include "serial_cli_controller.h"

Effect *Controller::effects[] = { new ColorEffect(), new FadeEffect() };
const int Controller::effectCount = sizeof(Controller::effects) / sizeof(Effect*);
Effect *Controller::currentEffect;

Controller *Controller::controllers[] = { new SerialCLIController() };
const int Controller::controllerCount = sizeof(Controller::controllers) / sizeof(Controller*);

Controller::Controller()
{
}

void Controller::init()
{
    // Load the current effect from NVRAM
    byte effect = EEPROM.read(2);
    if( effect != 255 ) // LED OFF
    {
        currentEffect = effects[effect];
        currentEffect->start();
    }

    // Load the duration from NVRAM
    EEPROM.get(3, Effect::m_duration);

    for(int i = 0; i < controllerCount; ++i)
    {
        controllers[i]->init();
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
