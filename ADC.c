#include <avr/io.h>
#include <avr/interrupt.h>

#include "ADC.h"

void adc_init()
{
	ADMUX = 0x00; //ADC Multiplexer Selection Register. S�tter till dess reset-v�rde. 
	ADMUX |= (1 << REFS0); //ADC Multiplexer Selection Register. S�tter 7e (REFS0) biten till 1 f�r reference voltage Vcc.
	ADMUX |= (1 << ADLAR); //ADC Multiplexer Selection Register. S�tter 6e (ADLAR) biten till 1 f�r left adjusted.

	ADCSRA = 0x00; //ADC Control and Status Register A. S�tter till dess reset-v�rde. 
	ADCSRA |= (1 << ADEN); //ADC Control and Status Register A. S�tter 8e (ADEN) biten till 1 f�r att aktivera ADC.
	ADCSRA |= (1 << ADIE);//ADC Control and Status Register A. S�tter 4e (ADIE) biten till 1 f�r att aktivera interrupt on completion.
	ADCSRA |= (1 << ADPS1) | (1 << ADPS0); //ADC Control and Status Register A. S�tter 1a (ADPS0) och 2a (ADPS1) biten till 1 f�r prescaler 8.

	sei();
}