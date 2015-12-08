#ifndef SOFT_SERIAL_CLI_INTERFACE_H
#define SOFT_SERIAL_CLI_INTERFACE_H

#include "controller.h"

class SoftSerialCLIController : public Controller
{
public:
    SoftSerialCLIController();
    void init();
    void update();

private:
    String command = "";
    void execCommand();
    int hex2bin( const char *s );
};

#endif // SOFT_SERIAL_CLI_INTERFACE_H
