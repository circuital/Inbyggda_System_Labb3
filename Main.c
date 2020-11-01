#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>

#include <util/delay.h>

#include "Serial.h"
#include "Timer.h"
#include "Button.h"

int buttonState = 0;
int lastButtonState = 0;

int main(void) 
{
	uart_init();
    button_init();

    while (1)
    {
        //Deluppgift 2
        set_button_state(&buttonState);
        print_button_state(&buttonState, &lastButtonState);
    }
}

