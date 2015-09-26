#include "serial_cli_controller.h"

#include <Arduino.h>
#include <EEPROM.h>
#include "fade_effect.h"
#include "activecolor_effect.h"

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
    else if ( command.startsWith("c ") ) {
      int offset = 0, temp;
      int R = command.substring(2).toInt();
      temp = R; do { ++offset; temp /= 10; } while (temp);
      int G = command.substring(3 + offset).toInt();
      temp = G; do { ++offset; temp /= 10; } while (temp);
      int B = command.substring(4 + offset).toInt();
      if( strcmp(currentEffect->name(), "activecolor") == 0 ) {
        ActiveColorEffect *acolor = static_cast<ActiveColorEffect*>(currentEffect);
        acolor->setColor( (byte)R , (byte)G, (byte)B );
        acolor->update();
      }
    }
    else if ( command.startsWith("b ") ) {
      int offset = 0, temp;
      byte R = command.substring(3, 4)[0];
      byte G = command.substring(4, 5)[0];
      byte B = command.substring(5, 6)[0];
      if( strcmp(currentEffect->name(), "activecolor") == 0 ) {
        ActiveColorEffect *acolor = static_cast<ActiveColorEffect*>(currentEffect);
        acolor->setColor( R , G, B );
        acolor->update();
      }
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
