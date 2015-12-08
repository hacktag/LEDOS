#include <Arduino.h>
#include "config.h"
#include "led.h"
#include "effect.h"
#include "controller.h"
#include <SoftwareSerial.h>
#include <ESP8266TrueRandom.h>

Controller controller;


void setup()
{
    Serial.begin(115200);
    
//    delay(3000);
//    analogWriteFreq(2000);

    pinMode(LED_R_PIN, OUTPUT);
    pinMode(LED_G_PIN, OUTPUT);
    pinMode(LED_B_PIN, OUTPUT);
    Led::setRGB(0,0,0);
    
    controller.init();
}

void loop() {
  controller.update();    
}
