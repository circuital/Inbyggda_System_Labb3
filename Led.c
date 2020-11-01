#include <avr/io.h>

#include "Led.h"

void led_init()
{
    DDRD |= (1 << PD6); //Sätter bit PD6 i port D till output.
}

int simple_ramp()
{
    /**
    * Inkrementerar variabeln bri med 1 upp till och med 255 och dekrementerar därefter bri ner till och med 0. Returnerar bri.
     */
    static int dir = 1;
    static int bri = 0;
    if (dir == 1)
    {
        bri++;
        if (bri == 255)
        {
            dir = -1;
        }
    }
    else
    {
        bri--;
        if (bri == 0)
        {
            dir = 1;
        }
    }
    return bri;
}

