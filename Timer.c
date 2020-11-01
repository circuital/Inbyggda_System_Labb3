#include <avr/io.h>
#include <avr/interrupt.h>

#include "Timer.h"

void timer_init()
{
	TCCR0A = 0x00; //Timer/Counter Control Register 0 A. Sätter till dess reset - värde.
	TCCR0A |= (1 << WGM00) | (1 << WGM01) | (1 << COM0A1); //Timer/Counter Control Register 0 A. Sätter 1a (WGM00), 2a (WGM01) och 8e (COM0A1) biten till 1 för fast PWM non invert mode. 

	TCCR0B = 0x00; //Timer/Counter Control Register 0 B. Sätter till dess reset - värde.
	TCCR0B |= (1 << CS00) | (1 << CS01); //Timer/Counter Control Register 0 B. Sätter 1a (CS00) och 2a (CS01) biten till 1 för prescaler=64.

	TCCR2A = 0x00; //Timer/Counter Control Register 2 A. Sätter till dess reset-värde. 
	TCCR2A |= (1 << WGM21); //Timer/Counter Control Register 2 A. Sätter 2a (WGM21) biten till 1 för CTC mode. 

	TCCR2B = 0x00; //Timer/Counter Control Register 2 B. Sätter till dess reset-värde. 
	TCCR2B |= (1 << CS20) | (1 << CS21) | (1 << CS22); //Timer/Counter Control Register 2 B. Sätter 1a (CS20), 2a (CS21) och 3a (CS22) biten till 1 för prescaler=1024.

	TCNT2 = 0x00; //Timer/Counter Register (stores the counter value). Sätter till 0 för att initiera.
	OCR2A = 0x9C; //Output Compare Register. Sätter till 156. 

	TIMSK2 = 0x00; //Timer/Counter Interrupt Mask Register 2. Sätter till dess reset-värde. 
	TIMSK2 |= (1 << OCIE2A); //Timer/Counter Interrupt Mask Register 2. Sätter 2a (OCIE2A) biten till 1 för interrupt on compare match.

	sei();
}

