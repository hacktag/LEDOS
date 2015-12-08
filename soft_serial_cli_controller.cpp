#include "config.h"
#include "controller.h"
#include "soft_serial_cli_controller.h"
#include <SoftwareSerial.h>

SoftwareSerial SoftSerial(SOFT_SERIAL_RX_PIN,SOFT_SERIAL_TX_PIN,128);

SoftSerialCLIController::SoftSerialCLIController()
{
}

void SoftSerialCLIController::init()
{
    
    SoftSerial.begin(19200);
    // A nice prompt for input output
    SoftSerial.println("Welcome to LEDOS");
    SoftSerial.println("How can I be of assistance?");
    SoftSerial.print(">");
}

void SoftSerialCLIController::update()
{
    while( SoftSerial.available() > 0 ) {
        char byte;
        SoftSerial.readBytes(&byte, 1);
        if( byte == '\n' )
        {
            execCommand();
        } else {
            // Discard carriage return and append byte
            if( byte != '\r' ) {
              command += byte;
            }
            // Discard commands longer than 255 symbols
            if( command.length() > 255 )
                command = "";
        }
    }
}

void SoftSerialCLIController::execCommand()
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
    else if (command == "effect brightness up") // EFFECT BRIGHTNESS UP
    {
//        SoftSerial.println(currentEffect->brightness());
        currentEffect->brightness((currentEffect->brightness()*2 < 256) ? currentEffect->brightness()*2 :255 );
//        SoftSerial.println(currentEffect->brightness());
//        SoftSerial.println();
    }
    else if (command == "effect brightness down") // EFFECT BRIGHTNESS DOWN
    {
//        SoftSerial.println(currentEffect->brightness());
        currentEffect->brightness(currentEffect->brightness()/2);
//        SoftSerial.println(currentEffect->brightness());
//        SoftSerial.println();
    }
    else if (command == "effect duration up") // EFFECT DURATION UP
    {
//        SoftSerial.println(currentEffect->duration());
        currentEffect->duration(currentEffect->duration()*2);
//        SoftSerial.println(currentEffect->duration());
//        SoftSerial.println();
    }
    else if (command == "effect duration down") // EFFECT DURATION DOWN
    {
//        SoftSerial.println(currentEffect->duration());
        currentEffect->duration(currentEffect->duration()/2);
//        SoftSerial.println(currentEffect->duration());
//        SoftSerial.println();
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
      SoftSerial.println("White balance set to "+Led::getWhiteValue());
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
//      SoftSerial.print("set HSV to ");
//      SoftSerial.print(hue);
//      SoftSerial.print(" ");
//      SoftSerial.print(sat);
//      SoftSerial.print(" ");
//      SoftSerial.println(val);
      setHSV(hue,sat,val);
    }
    else if ( command.startsWith("effect ") ) {
      bool error = true;
      for(int i = 0; i < effectCount; ++i) // EFFECT NAME
        {
            if( command == (String("effect ") + effects[i]->name()) )
            {
                currentEffect->stop();
                currentEffect = effects[i];
                currentEffect->init();
                currentEffect->start();
                error = false;
            }
        }
        if (error) SoftSerial.println("Unrecognised effect.");    
    }
    else if ( command.startsWith("effects") ) {
      SoftSerial.print("Available effects: ");
      for(int i = 0; i < effectCount; ++i) // EFFECT NAME
        {
            SoftSerial.print(effects[i]->name());
            SoftSerial.print(", ");
        }
        SoftSerial.println();
    }
    
    else {
        // If an effect is not found display an error
        SoftSerial.println("Unrecognised command.");
    }

    // Discard the current command
    command = "";
}

int SoftSerialCLIController::hex2bin( const char *s )
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
