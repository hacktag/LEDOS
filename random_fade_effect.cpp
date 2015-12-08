#include "random_fade_effect.h"
#include <ESP8266TrueRandom.h>
void RandomFadeEffect::init()
{
    rgbStep = 1;
    sat = 1;
    pickRandomColor();
    renderTime = millis(); 
}

void RandomFadeEffect::update()
{
    if( millis() < renderTime ) return;

    if (R() > rgb[0]) {  
    R(R()-rgbStep);  
    }   
    if (R() < rgb[0]) {  
    R(R()+rgbStep);
    }  
    if (G() > rgb[1]) {  
    G(G()-rgbStep);
    }   
    if (G() < rgb[1]) {  
    G(G()+rgbStep);
    }  
    if (B() > rgb[2]) {  
    B(B()-rgbStep);
    }   
    if (B() < rgb[2]) {  
    B(B()+rgbStep);
    }  
    
    // If all colors match get new colors  
    if (R() == rgb[0]) {  
      if (G() == rgb[1]) {  
        if (B() == rgb[2]) {  
          pickRandomColor();
        }  
      }  
    }    

//    // Recalculate distance to account for user input deviation
//    distance = abs(R()-rgb[0]) + abs(G()-rgb[1]) + abs(B()-rgb[2]);
    
    renderTime += ceil((float)m_duration / distance );
}

void RandomFadeEffect::pickRandomColor()
{
    hue = (float)ESP8266TrueRandom.random(200)/200;
    sat = (float)ESP8266TrueRandom.random(160,200)/200;
    val = (float)m_brightness/255;
    hsvToRgb(hue, sat, val, rgb);
    distance = abs(R()-rgb[0]) + abs(G()-rgb[1]) + abs(B()-rgb[2]);
}
