/*	Author: Rishab Dudhia (rdudh001)
 *  Partner(s) Name: 
 *	Lab Section:022
 *	Assignment: Lab #4  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *	A0 increments; A1 decrements; PORTC starts at 7
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {smstart, wait, inc, dec, inc_wait, dec_wait, reset } state;
unsigned char cntA0;
unsigned char cntA1;
void Tick()
{
    unsigned char actualC = PINC ;
    //unsigned char tempC = PORTC & 0x03;
    switch(state)
    {
	case smstart:
	    state = wait;
	    break;
	case wait:
	    if (((PINA & 0x03) == 0x01) && (PORTC < 0x09))
	    {
		state = inc;
	    	cntA0 = cntA0 + 1;
	    }
	    else if (((PINA & 0x03) == 0x02) && (PORTC > 0x00))
	    {
		state = dec;
	        cntA1 = cntA1 + 1;
	    }
	    else
	    {
		state = wait;
	    }
	    break;
	case inc_wait:
	    if((PINA & 0x03) == 0x01)
	    {
		state = inc_wait;
	    }
	    else if ((PINA & 0x03) == 0x02)
	    {
		state = dec;
		cntA1 = cntA1 + 1;
	    }
	    else if ((PINA & 0x03) == 0x00)
	    {
		state = reset;
	    }
	    else
	    {
		state = wait;
	    }
	    break;
	case dec_wait:
	    if ((PINA & 0x03) == 0x02)
	    {
		state = dec_wait;
	    }
	    else if ((PINA & 0x03) == 0x01)
	    {
		state = inc;
		cntA0 = cntA0 + 1;
	    }
	    else if ((PINA & 0x03) == 0x00)
	    {
		state = reset;
	    }
	    else
	    {
		state = wait;
	    }
	    break;
	case inc:
	    state = inc_wait;
	    break;
	case dec:
	    state = dec_wait;
	    break;
	case reset:
	    state = wait;
	    break;

        default:
	    state = smstart;
	    break;
    }

    switch(state)
    {
        case smstart:
	    PORTC = 0x07;
        case wait:
        case inc_wait:
        case dec_wait:
	    break;
        case inc:
            actualC = actualC + 1;
	    PORTC = actualC;
            break;
	case dec:
	    actualC = actualC - 1;
	    PORTC = actualC;
	    break;
	case reset:
	    PORTC = 0x00;
	    break;
        default:
            break;
    }
}
int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x07;
    cntA0 = 0x00;
    cntA1 = 0x00;
    state = smstart;
    /* Insert your solution below */
    while (1) {
	Tick();
    }
    return 0;
}