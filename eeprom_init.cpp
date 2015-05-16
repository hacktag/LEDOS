#include "eeprom_init.h"

#include <EEPROM.h>
#include "config.h"

EEPROMInit::EEPROMInit()
{
    unsigned short schema;
    EEPROM.get(0, schema);
    if( schema != EEPROM_SCHEMA )
    {
        // Inital state should be OFF
        EEPROM.write(2, 255);

        // Initialise default duration
        unsigned int duration = 10000;
        EEPROM.put(3, duration);

        // Initialise Active Color Spaces
        char color[3] = {255, 255, 255};
        for(int i = 9; i < 20; i += 3) {
            EEPROM.put(i, color);
        }

        // Write EEPROM SCHEMA
        schema = EEPROM_SCHEMA;
        EEPROM.put(0, schema);
    }
}
