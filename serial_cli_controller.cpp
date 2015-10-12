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
    if ( command[0] == 'b' ) {
      LEDColor::R( hex2bin( command.substring(1, 3).c_str() ) );
      LEDColor::G( hex2bin( command.substring(3, 5).c_str() ) );
      LEDColor::B( hex2bin( command.substring(5, 7).c_str() ) );
    }
    else if (command == "shutdown") // SHUTDOWN
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
      LEDColor::R( temp = command.substring(2).toInt() );
      do { ++offset; temp /= 10; } while (temp);
      LEDColor::G( temp = command.substring(3 + offset).toInt() );
      do { ++offset; temp /= 10; } while (temp);
      LEDColor::B( command.substring(4 + offset).toInt() );
    }
    else if ( command.startsWith("w ") ) {
      int offset = 0;
      float temp;
      LEDColor::RFactor( temp = command.substring(2).toFloat() );
      do { ++offset; temp /= 10; } while (temp);
      LEDColor::GFactor( temp = command.substring(3 + offset).toFloat() );
      do { ++offset; temp /= 10; } while (temp);
      LEDColor::BFactor( command.substring(4 + offset).toFloat() );
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
}

int SerialCLIController::hex2bin( const char *s )
{
  int ret = 0;
  int i;
  for( i=0; i<2; i++ )
  {
    char c = *s++;
    int n=0;
    if( '0'<=c && c<='9' )
      n = c-'0';
    else if( 'a'<=c && c<='f' )
      n = 10 + c-'a';
    else if( 'A'<=c && c<='F' )
      n = 10 + c-'A';
    ret = n + ret*16;
  }
  return ret;
}
