#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>

#include "Serial.h"
#include "Button.h"

void button_init()
{
    DDRD &= ~(1 << PD2); //Sätter bit PD2 i port D till input.
}

void set_button_state(int* buttonState)
{
    /**
    * State machine för knappen, ändrar variabeln buttonState.
    */
    if (PIND & (1 << PD2))
    {
        *buttonState = 1;
    }
    else if (!(PIND & (1 << PD2)))
    {
        *buttonState = 0;
    }
}

void print_button_state(int* buttonState, int* lastButtonState, int* setLedState)
{
    /**
    * Skriver ut om knappen är nedtryckt eller släppt i serieterminalen. Om släppt sätts variablen setLedState, som används i funktionen set_led_state(), till 1.
    */
    if (*buttonState == 1 && *lastButtonState == 0)
    {
        printf_P(PSTR("pushed\n\r"));
    }
    else if (*buttonState == 0 && *lastButtonState == 1)
    {
        printf_P(PSTR("released\n\r"));
        *setLedState = 1;
    }
    *lastButtonState = *buttonState;
}