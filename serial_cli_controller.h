#ifndef SERIAL_CLI_INTERFACE_H
#define SERIAL_CLI_INTERFACE_H

#include "controller.h"

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

#endif // SERIAL_CLI_INTERFACE_H
