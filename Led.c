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

void set_led_state(int* setLedState, LED_STATE* ledState)
{
    /**
    * State machine för LEDen, ändrar variabeln ledState OM variablen setLedState är lika med 1, och nollställer isåfall även setLedState.
    */
    if (*setLedState == 1)
    {
        if (*ledState == PULSE)
        {
            *ledState = POT;
        }
        else if (*ledState == POT)
        {
            *ledState = BLINK;
        }
        else if (*ledState == BLINK)
        {
            *ledState = OFF;
        }
        else if (*ledState == OFF)
        {
            *ledState = PULSE;
        }
        *setLedState = 0;
    }
}


void led_command(int* adc, LED_STATE* ledState)
{
    /**
    * Kollar nuvarande ledState och startar motsvarande funktionalitet.
    */
    if (*ledState == PULSE)
    {
        TCCR0A |= (1 << COM0A1); //Sätter 8e (COM0A1) biten i TCCR0A (Timer/Counter Control Register 0 A ) till 1 för att connecta OCR0A (Output compare Register).
        OCR0A = simple_ramp();
    }
    else if (*ledState == POT)
    {
        ADCSRA |= (1 << ADSC); //Startar ADC omvandling i single conversion mode.
        if (*adc == 0)
        {
            TCCR0A &= ~(1 << COM0A1); //Sätter 8e (COM0A1) biten i TCCR0A (Timer/Counter Control Register 0 A ) till 0 för att disconnecta OCR0A (Output compare Register).
        }
        else
        {
            TCCR0A |= (1 << COM0A1); //Sätter 8e (COM0A1) biten i TCCR0A (Timer/Counter Control Register 0 A ) till 1 för att connecta OCR0A (Output compare Register).
            OCR0A = *adc;
        }
    }
    else if (*ledState == BLINK)
    {
        static int counter = 0;
        if (counter == 100)
        {
            TCCR0A ^= (1 << COM0A1); //Togglar 8e (COM0A1) biten i TCCR0A (Timer/Counter Control Register 0 A ) till 1/0 för att connecta/disconnecta OCR0A (Output compare Register).
            OCR0A = 255;
            counter = 0;
        }
        else
        {
            counter++;
        }
    }
    else if (*ledState == OFF)
    {
        TCCR0A &= ~(1 << COM0A1); //Sätter 8e (COM0A1) biten i TCCR0A (Timer/Counter Control Register 0 A ) till 0 för att disconnecta OCR0A (Output compare Register).
    }
}

