#include "rgb_fade_effect.h"

void RGBFadeEffect::init()
{
    // Handle a corner case in which the update just increments
    // a color and overflows the byte
    if( R() == m_brightness ) R(m_brightness-1);
    if( G() == m_brightness ) G(m_brightness-1);
    if( B() == m_brightness ) R(m_brightness-1);
    if( R() == 0 ) R(1);
    if( G() == 0 ) G(1);
    if( B() == 0 ) R(1);
    stage = 0;
    renderTime = millis();
}

void RGBFadeEffect::update()
{
    if( millis() < renderTime ) return;

    switch(stage)
    {
    case 0:
        if( G( G()+1 ) == m_brightness ) ++stage;
        break;
    case 1:
        if( R( R()-1 ) == 0 ) ++stage;
        break;
    case 2:
        if( B( B()+1 ) == m_brightness ) ++stage;
        break;
    case 3:
        if( G( G()-1 ) == 0 ) ++stage;
        break;
    case 4:
        if( R( R()+1 ) == m_brightness ) ++stage;
        break;
    case 5:
        if( B( B()-1 ) == 0 ) ++stage;
        break;
    }
    if( stage == 6 )
        stage = 0;
  
    renderTime += ceil((float)m_duration / (m_brightness*6));
}
