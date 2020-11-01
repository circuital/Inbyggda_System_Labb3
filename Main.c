#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>

#include <util/delay.h>

#include "Serial.h"
#include "Timer.h"
#include "Button.h"
#include "Led.h"
#include "ADC.h"


int buttonState = 0;
int lastButtonState = 0;
int setLedState = 0;
LED_STATE state = PULSE;
int adc;

ISR(ADC_vect) //Triggad vid avslutat ADC-omvandling. 
{
    adc = ADCH;
}

ISR(TIMER2_COMPA_vect) //Triggad vid compare match. 
{
    //Deluppgift 3
    //ADCSRA |= (1 << ADSC); //start conversion in single conversion mode
    //OCR0A = adc;

    //Deluppgift 4
    set_button_state(&buttonState);
    print_button_state(&buttonState, &lastButtonState, &setLedState);
    set_led_state(&setLedState, &state);
    led_command(&adc, &state);
}

int main(void) 
{
	uart_init();
    timer_init();
    led_init();
    button_init();
    adc_init();

    while (1)
    {
        //Deluppgift 2
        /*set_button_state(&buttonState);
        print_button_state(&buttonState, &lastButtonState);*/

        //Deluppgift 3

        //Deluppgift 4
    }
}

