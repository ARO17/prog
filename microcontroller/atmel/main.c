#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>

#define F_CPU 1000000UL
#include <util/delay.h>

int main (void) {
    //    DDRD |= (1 << PD6); // Set PD6 as output pin

    // Set PD6 as output pin and PD0 as input pin
    DDRD = DDRD | (1 << PD6) & ~(1 << PD0);
    // Set PB1 as output pin
    DDRB |= (1 << PB1);
    // Enable pull-up resistor on PD0
    PORTD |= (1 << PD0);

    //    DDRA &= ~(1 << PA1); // Set PA1 as input pin
    //    PORTA |= (1 << PA1); // Enable pull-up resistor
    
    while (1) {
	//	if (!(PINA & (1 << PA1))) // switch is closed, 0 on PA1 pin
	if (!(PIND & (1 << PD0))) { // switch is closed, 0 on PD0 pin
	    PORTD |= (1 << PD6); // 1 on output PD6 pin, LED on
	    PORTB |= (1 << PB1); // 1 on outuput PB1, servos move
	    _delay_ms(1);
	    PORTB &= ~(1 << PB1);
	    _delay_ms(19);
	} else {
	    PORTD &= ~(1 << PD6); // 0 on output PD6 pin, LED off
	    PORTB |= (1 << PB1); // 1 on outuput PB1, servos move
	    _delay_ms(2);
	    PORTB &= ~(1 << PB1);
	    _delay_ms(18);
	}
    }
}
