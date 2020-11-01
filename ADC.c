#include <avr/io.h>
#include <avr/interrupt.h>

#include "ADC.h"

void adc_init()
{
	ADMUX = 0x00; //ADC Multiplexer Selection Register. Sätter till dess reset-värde. 
	ADMUX |= (1 << REFS0); //ADC Multiplexer Selection Register. Sätter 7e (REFS0) biten till 1 för reference voltage Vcc.
	ADMUX |= (1 << ADLAR); //ADC Multiplexer Selection Register. Sätter 6e (ADLAR) biten till 1 för left adjusted.

	ADCSRA = 0x00; //ADC Control and Status Register A. Sätter till dess reset-värde. 
	ADCSRA |= (1 << ADEN); //ADC Control and Status Register A. Sätter 8e (ADEN) biten till 1 för att aktivera ADC.
	ADCSRA |= (1 << ADIE);//ADC Control and Status Register A. Sätter 4e (ADIE) biten till 1 för att aktivera interrupt on completion.
	ADCSRA |= (1 << ADPS1) | (1 << ADPS0); //ADC Control and Status Register A. Sätter 1a (ADPS0) och 2a (ADPS1) biten till 1 för prescaler 8.

	sei();
}