#include "serial_cli_controller.h"

#include <Arduino.h>
#include <EEPROM.h>
#include "fade_effect.h"

SerialCLIController::SerialCLIController()
{
}

void SerialCLIController::init()
{
    // Initialise serial connection
    Serial.begin(115200);

    // A nice prompt for input output
    Serial.println("Wellcome to LEDOS");
    Serial.println("How can I be of assistance?");
    Serial.print(">");
}

void SerialCLIController::update()
{
    while( Serial.available() > 0 ) {
        char byte;
        Serial.readBytes(&byte, 1);
        if( byte == '\n' )
        {
            execCommand();
        } else {
            command += byte;
            // Discard commands longer than 255 symbols
            if( command.length() > 255 )
                command = "";
        }
    }
}

void SerialCLIController::execCommand()
{
    // Print the received command
    Serial.println(command);

    if (command == "shutdown") // SHUTDOWN
    {
        currentEffect->stop();
        currentEffect->reset();
        EEPROM.write(2, 255);
    }
    else if (command == "effect start") // EFFECT START
    {
        currentEffect->start();
    }
    else if (command == "effect stop") // EFFECT STOP
    {
        currentEffect->stop();
    }
    else if ( command.startsWith("effect set duration ") ) // EFFECT SET DURATION
    {
        currentEffect->duration(command.substring(20).toFloat() * 1000);
    }
    else
    {
        bool error = true;
        for(int i = 0; i < effectCount; ++i) // EFFECT NAME
        {
            if( command == (String("effect ") + effects[i]->name()) )
            {
                currentEffect = effects[i];
                currentEffect->init();
                currentEffect->start();
                EEPROM.write(2, i);
                error = false;
            }
        }

        // If an effect is not found display an error
        if( error ) Serial.println("Unrecognized command.");
    }

    // Discard the current command
    command = "";

    // New prompt
    Serial.print(">");
}
