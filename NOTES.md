Notes
=====

EEPROM
------
Below is a table describing the usage of the EEPROM memory by LEDOS.

| EEPROM Address | Usage Description                |
| -------------- | -------------------------------- |
| __[0-31]__     | Reserved for __```LEDOS ```__.   |
| [0-1]          | EEPROM Schema ID                 |
| [2]            | Represents the last effect set.  |
| [3-6]          | The last used effect duration.   |
| [9-11]         | Active Color Space 1             |
| [12-14]        | Active Color Space 2             |
| [15-17]        | Active Color Space 3             |
| [18-20]        | Active Color Space 4             |
