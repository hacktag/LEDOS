#ifndef SERIAL_CLI_CONTROLLER_H
#define SERIAL_CLI_CONTROLLER_H

#include "controller.h"
#include <Arduino.h>

class SerialCLIController : public Controller
{
public:
    SerialCLIController();
    void init();
    void update();

private:
    String command = "";
    void execCommand();
    int hex2bin( const char *s );
};

#endif // SERIAL_CLI_CONTROLLER_H
