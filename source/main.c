/*	Author: Rishab Dudhia (rdudh001)
 *  Partner(s) Name: 
 *	Lab Section:022
 *	Assignment: Lab #4  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *	Initially PB0 on and pressing PA0 turns B0 off and B1 on; repeat
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States { smstart, pb0_on, pb0_wait, pb1_on, pb1_wait } state;

unsigned char Tick(unsigned char cntA0)
{
    switch(state)
    {
	case smstart:
	    state = pb0_on;
	    break;
	case pb0_on:
	    if ((PINA & 0x01) == 0x01)
	    {
		state = pb0_wait;
	    }
	    else
	    {
		state = pb0_on;
	        cntA0 = cntA0 + 1;
	    }
	    break;
	case pb0_wait:
	    if((PINA & 0x01) == 0x01)
	    {
		state = pb0_wait;
	    }
	    else
	    {
		state = pb1_on;
	    }
	    break;
	case pb1_on:
	    if ((PINA & 0x01) == 0x01)
	    {
		state = pb1_wait;
	    }
	    else
	    {
		state = pb1_on;
	        cntA0 = cntA0 + 1;
	    }
	    break;
	case pb1_wait:
	    if ((PINA & 0x01) == 0x01)
	    {
		state = pb1_wait;
	    }
	    else
	    {
		state = pb0_on;
	    }
	    break;

	    default:
		state = smstart;
		break;
    }

    switch(state)
    {
        case smstart:
        case pb0_on:
            PORTB = 0x01;
	    return cntA0;
        case pb0_wait:
            PORTB = 0x02;
            return (cntA0);
        case pb1_on:
            PORTB = 0x02;
	    return cntA0;
        case pb1_wait:
            PORTB = 0x01;
            return (cntA0);

        default:
            return cntA0;
    }
}
int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    unsigned char cntA0 = 0x00;
    state = smstart;
    /* Insert your solution below */
    while (1) {
	cntA0 = Tick(cntA0);
    }
    return 0;
}
