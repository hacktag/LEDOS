#include <Arduino.h>
#include "config.h"
#include "led.h"
#include "effect.h"
#include "controller.h"

Controller controller;

void setup()
{
    Serial.begin(115200);
//    delay(1000);
    pinMode(LED_R_PIN, OUTPUT);
    pinMode(LED_G_PIN, OUTPUT);
    pinMode(LED_B_PIN, OUTPUT);
    Led::setRGB(0,0,0);

    controller.init();
    
}

void loop() {
  controller.update();    
}