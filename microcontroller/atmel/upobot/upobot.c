// Target : 2313
// Crystal: 8.0000Mhz
// avr-gcc -Os -g -Wall -mmcu=at90s2313 -o upobot.elf upobot.c

#include <avr/io.h>
#include <avr/interrupt.h>

// globals vars
unsigned char time;
unsigned char cSpeedD,cSpeedG; /* right and left motor speed */
unsigned char _cSD,_cSG; /* motor speed copy for calculation */
unsigned char sSenseD,cSenseG;
unsigned char _cPwmState; /* START, FALLING_EDGE1, FALLING_EDGE2 */
volatile unsigned int _uCptD,_uCptG; /* sensor motor (odometry) */

// globals defines
#define START 0x01
#define FALLING_EDGE1 0x02 /* Front descendant 1 */
#define FALLING_EDGE2 0x03 /* Front descendant 2 */

#define CAPTR 0x10 /* Right sensor  on PD4 */
#define CAPTF 0x20 /* Front sensor on PD5 */
#define CAPTL 0x40 /* Left sensor on PD6 */


void port_init(void)
{
    PORTB = 0x00; /* ? */
    DDRB  = 0x1F; /* PB0 -> PB4 as output, PB5, PB6, PB7 as input */ 
    PORTD = 0x00; /* ? */
    DDRD  = 0x00; /* PD0 -> PD7 as input */
}

//TIMER1 initialisation - prescale:1024
// desired value: 10mSec
void timer1_init(void)
{
    TCCR1B = 0x00; // stop timer

    TCNT1H = 0xFF; // set count value 65458
    TCNT1L = 0xB2; 

    OCR1H  = 0x1F; // set compare value 8000
    OCR1L  = 0x40;

    TCCR1A = 0x00; // Timer/Counter1 disconnected from output pin OC1 (PB3)

    TCCR1B = 0x05; // start Timer CS10 and CS12 bit set -> prescale 1024
}

ISR(TIMER1_OVF1_vect)
{
    //TIMER1 has overflowed
    time++;
    if (time == 60){ 
	time = 0;
	/* flashing led  */
	if ((PORTB & 0x10) == 0x10) /* If PB4 == 1 */
	    PORTB &= 0xEF;          /* PB4 = 0 */
	else
	    PORTB |= 0x10;          /* PB4 = 1 */
    } 

    TCNT1H = 0xFF; //reload counter high value
    TCNT1L = 0xB2; //reload counter low value
}

//TIMER0 initialisation - prescale:1
// desired value: 1mSec
void timer0_init(void)
{
    TCCR0 = 0x00; //stop timer
    TCNT0 = 0xF9; //set count
    _cPwmState = START;
    TCCR0 = 0x04; //start timer
}

ISR(TIMER0_OVF0_vect)
{
    //TIMER0 has overflowed

    unsigned char cTimer;
    TCCR0 = 0x00; //stop timer

    switch (_cPwmState){
    case START :
	_cSD = cSpeedD; // keeping speed value until end of cycle
	_cSG = cSpeedG;
	PORTB |= 0x0C; // rising edge on PORTB,2 & PORTB,3
	// PORTB |= (1 << PB2 | 1 << PB3);
	if (_cSD > _cSG)
	    cTimer = (unsigned char)(0xFF - _cSG);
	else
	    cTimer = (unsigned char)(0xFF - _cSD);
	_cPwmState = FALLING_EDGE1;
	break;
    case FALLING_EDGE1 :
	if (_cSD == _cSG){
	    cTimer = _cSD;
	    PORTB &= 0xF3; /* stop/disable both motors */
	    _cPwmState = START;
	} 
	else {
	    if (_cSD > _cSG) {
		PORTB &= 0xFB;  //falling edge on PORTB,2
		//PORTB &= ~(1 << PB2);
		//PORTB &= ~(0x04);
		cTimer = (unsigned char)(0xFF - (unsigned char)(_cSD - _cSG));
	    }
	    else {
		PORTB &= 0xF7; // falling edge on PORTB,3
		cTimer = (unsigned char)(0xFF - (unsigned char)(_cSG - _cSD));
	    }
	    _cPwmState = FALLING_EDGE2;
	} 	 
	break;
    case FALLING_EDGE2 :
	PORTB &= 0xF3; /* stop/disable both motors */
	if (_cSD > _cSG)
	    cTimer = _cSD;
	else
	    cTimer = _cSG;
	_cPwmState = START;
	break;
    }
    TCNT0 = cTimer; //set count
    TCCR0 = 0x04; //start timer
}

//UART0 initialisation
// desired baud rate: 38400
// actual: baud rate:38462 (0,2%)
void uart0_init(void)
{
    UCR  = 0x00; //disable while setting baud rate
    UBRR = 0x0C; //set baud rate
    UCR  = 0xB8; //enable
}

ISR(UART_RX_vect)
{
    //uart has received a character in UDR
}

ISR(UART_UDRE_vect)
{
    //character transferred to shift register so UDR is now empty
}

ISR(INT0_vect)
{
    //external interupt on INT0
    _uCptD++;
}

ISR(INT1_vect)
{
    //external interupt on INT1
    _uCptG++;
}
 
//call this routine to initialise all peripherals
void init_devices(void)
{
    //stop errant interrupts until set up
    cli(); //disable all interrupts
    port_init();
    //timer0_init();
    timer1_init();
    uart0_init();

    MCUCR = 0x0A;
    GIMSK = 0xC0;
    TIMSK = 0x82;
    sei(); //re-enable interrupts
    //all peripherals are now initialised
    _uCptG = 0;
    _uCptD = 0;
}

int main(void)
{
    time = 0;
    init_devices();
    //insert your functional code here...
    PORTB = 0x03; // Run motor right and left, PB0 and PB1, forward
    PORTB &= 0xF3; // disable motors
    cSpeedD = 0xD0;
    cSpeedG = 0xD0;
    while (1) {

	if ((PIND & CAPTF) == 0x00) { /* obstacle detected ahead */
	    //PORTB &= 0xFD; /* TEST moteur gauche sens antihoraire */
	    //PORTB &= 0xFE; /* TEST moteur droit sens horaire */
	    PORTB |= (1 << PB3);
	    while (_uCptG < 5) {} /* TEST */
	    //PORTB |= 0x01; /* TEST moteur droit sens horaire */
	    PORTB &= ~(1 << PB3);
	    
#ifdef NOTDEF
	    PORTB &= 0xFC;            /* reverse */
	    cSpeedD = 0xD0;           /* set default speed to the right motor */
	    cSpeedG = 0xD0;           /* set default speed to the left motor */
	    _uCptD = 0;               /* reset motor's right sensor  */
	    _uCptG = 0;               /* reset motor's left sensor  */

	    while ((_uCptD < 5) & (_uCptG < 5)) {}
	    PORTB |= 0x01;
	    _uCptD = 0;
	    _uCptG = 0;
	    while ((_uCptD < 21) & (_uCptG < 21)) {}
	    PORTB |= 0x03; /* forward */
#endif
	}
	else PORTB |= 0x03; /* forward */

	if ((PIND & CAPTR) == 0x00) /* obstacle on the right */
	    cSpeedG = 0x00;         /* Stop left motor to turn left */
	else
	    cSpeedG = 0xD0;         /* let the left motor at normal speed */
 
	if ((PIND & CAPTL) == 0x00) /* obstacle on the left */
	    //cSpeedD = 0x00;         /* Stop right motor to turn right */
	    PORTB &= 0xF7;
	else
	    cSpeedD = 0xD0;         /* let the right motor at normal speed */

    }
}
