#include <Arduino.h>
#include "config.h"
#include "controller.h"
#include "eeprom_init.h"

Controller controller;

void setup()
{
    pinMode(LED_R_PIN, OUTPUT);
    pinMode(LED_G_PIN, OUTPUT);
    pinMode(LED_B_PIN, OUTPUT);
    analogWrite(LED_R_PIN, 0);
    analogWrite(LED_G_PIN, 0);
    analogWrite(LED_B_PIN, 0);

    EEPROMInit();

    controller.init();
}

void loop() {
    controller.update();
}
