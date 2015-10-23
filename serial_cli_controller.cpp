#include "controller.h"
#include "serial_cli_controller.h"

SerialCLIController::SerialCLIController()
{
}

void SerialCLIController::init()
{
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
    if ( command[0] == 'b' || command[0] == '#') {
      R( hex2bin( command.substring(1, 3).c_str() ) );
      G( hex2bin( command.substring(3, 5).c_str() ) );
      B( hex2bin( command.substring(5, 7).c_str() ) );
    }
    else if (command == "shutdown") // SHUTDOWN
    {
        currentEffect->stop();
        currentEffect->reset();
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
        currentEffect->duration(command.substring(20).toInt());
    }
    else if ( command.startsWith("effect set brightness ") ) // EFFECT SET BRIGHTNESS
    {
        currentEffect->brightness(command.substring(22).toInt());
    }
    else if ( command.startsWith("c ") ) {
      int offset = 0, temp;
      R( temp = command.substring(2).toInt() );
      do { ++offset; temp /= 10; } while (temp);
      G( temp = command.substring(3 + offset).toInt() );
      do { ++offset; temp /= 10; } while (temp);
      B( command.substring(4 + offset).toInt() );
    }
    else if ( command.startsWith("w ") ) {
      int offset = 0;
      int temp;
      whiteR( temp = command.substring(2).toInt() );
      do { ++offset; temp /= 10; } while (temp);
      whiteG( temp = command.substring(3 + offset).toInt() );
      do { ++offset; temp /= 10; } while (temp);
      whiteB( command.substring(4 + offset).toInt() );
      setRGB(R(),G(),B());
    }
    else if ( command.startsWith("h ") ) {
      int offset_a, offset_b;
      float hue,sat,val;
      offset_b = command.indexOf(' ',2) ;
      hue = command.substring(2,offset_b).toFloat();
      offset_a = command.indexOf(' ',offset_b+1);
      sat = command.substring(offset_b,offset_a).toFloat();
      val = command.substring(offset_a).toFloat();
//      Serial.print("set HSV to ");
//      Serial.print(hue);
//      Serial.print(" ");
//      Serial.print(sat);
//      Serial.print(" ");
//      Serial.println(val);
      setHSV(hue,sat,val);
    }
    else if ( command.startsWith("effect ") ) {
      bool error = true;
      for(int i = 0; i < effectCount; ++i) // EFFECT NAME
        {
            if( command == (String("effect ") + effects[i]->name()) )
            {
                currentEffect = effects[i];
                currentEffect->init();
                currentEffect->start();
                error = false;
            }
        }
        if (error) Serial.println("Unrecognized effect.");    
    }
    else if ( command.startsWith("effects") ) {
      Serial.print("Available effects: ");
      for(int i = 0; i < effectCount; ++i) // EFFECT NAME
        {
            Serial.print(effects[i]->name());
            Serial.print(", ");
        }
        Serial.println();
    }
    
    else {
        // If an effect is not found display an error
        Serial.println("Unrecognized command.");
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
