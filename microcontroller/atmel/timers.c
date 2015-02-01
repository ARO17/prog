/*
 * timers.c -- Training timer usage
 * 
 * Written by Harold André
 * E-mail     <harold.andre@gmx.fr>
 * 
 * Started on  Sat Jan 10 23:47:48 2015 Harold André
 * Last update Sun Jan 11 14:39:15 2015 Harold André
 * 
 */

#include <avr/io.h>

int main(void)
{
    unsigned char elapsedSeconds = 0;

    DDRD |= (1 << 0);		// Set LED as output

    TCCR1B |= ((1 << CS10) | (1 << CS11));	// Set up timer with prescaler of 64

    for (;;) {
	// Check timer value in if statement, true when count matches 1/20 of second
	if (TCNT1 >= 15624) {

	    TCNT1 = 0;		// Reset timer value
	    elapsedSeconds++;

	    if (elapsedSeconds == 5) {
		elapsedSeconds = 0;
		PORTD ^= (1 << 6);	// Toggle the LED
	    }
	    
	}
    }
}
