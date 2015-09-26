#include "fade_effect.h"

unsigned int FadeEffect::maxDelay()
{
    return -1;
}

void FadeEffect::init()
{
    // Handle a corner case in which the update just increments
    // a color and overflows the byte
    if( R() == 255 ) R(254);
    if( G() == 255 ) G(254);
    if( B() == 255 ) R(254);
    if( R() == 0 ) R(1);
    if( G() == 0 ) G(1);
    if( B() == 0 ) R(1);
    stage = 0;
    renderTime = 0;
}

void FadeEffect::update()
{
    if( millis() < renderTime ) return;

    switch(stage)
    {
    case 0:
        if( G( G()+1 ) == 255 ) ++stage;
        break;
    case 1:
        if( R( R()-1 ) == 0 ) ++stage;
        break;
    case 2:
        if( B( B()+1 ) == 255 ) ++stage;
        break;
    case 3:
        if( G( G()-1 ) == 0 ) ++stage;
        break;
    case 4:
        if( R( R()+1 ) == 255 ) ++stage;
        break;
    case 5:
        if( B( B()-1 ) == 0 ) ++stage;
        break;
    }
    if( stage == 6 )
        stage = 0;

    renderTime += ceil((float)m_duration / 1536);
}
