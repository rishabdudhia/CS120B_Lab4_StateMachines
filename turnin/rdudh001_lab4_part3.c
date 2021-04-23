/*	Author: Rishab Dudhia (rdudh001)
 *  Partner(s) Name: 
 *	Lab Section:022
 *	Assignment: Lab #4  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *	Deadbolt A2 = '#' A1 = 'Y' A0 = 'X' A7 = lock;B0: 1 = unlocked; B0: 0 = locked; combination to unlock: press #, release #, press Y
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {smstart, wait_hash_p, wait_hash_r, wait_y, unlocked, locked, wait_l } state;
unsigned char cntA0;
unsigned char cntA1;
unsigned char cntA2;
unsigned char cntA7;
void Tick()
{
    //unsigned char actualC = PINC ;
    unsigned char tempA = PINA & 0x87;
    switch(state)
    {
	case smstart:
	    state = wait_hash_p;
	    break;
	case wait_hash_p:
	    if (tempA == 0x04)
	    {
		state = wait_hash_r;
	    	cntA2 = cntA2 + 1;
	    }
	    else if (tempA == 0x80)
	    {
		state = locked;
	        cntA7 = cntA7 + 1;
	    }
	    else if (tempA == 0x02)
	    {
		state = wait_hash_p;
		//cntA1 = cntA1 + 1;
	    }
	    else if (tempA == 0x01)
	    {
		state = wait_hash_p;
		//cntA0 = cntA0 + 1;
	    }
	    else
	    {
		state = wait_hash_p;
	    }
	    break;
	case wait_hash_r:
	    if(tempA == 0x00)
	    {
		state = wait_y;
	    }
	    else if (tempA == 0x04)
	    {
		state = wait_hash_r;
	    }
	    else if (tempA == 0x80)
	    {
		state = locked;
		cntA7 = cntA7 + 1;
	    }
	    else if (tempA == 0x02)
	    {
		state = wait_hash_p;
		cntA1 = cntA1 + 1;
	    }
	    else if (tempA == 0x01)
	    {
		state = wait_hash_p;
		cntA0 = cntA0 + 1;
	    }
	    else
	    {
		state = wait_hash_p;
	    }
	    break;
	case wait_y:
            if(tempA == 0x00)
            {
                state = wait_y;
            }
            else if (tempA == 0x04)
            {
                state = wait_hash_p;
		cntA2 = cntA2 + 1;
            }
            else if (tempA == 0x80)
            {
                state = locked;
                cntA7 = cntA7 + 1;
            }
            else if (tempA == 0x02)
            {
                state = unlocked;
                cntA1 = cntA1 + 1;
            }
	    else if (tempA == 0x01)
	    {
		state = wait_hash_p;
		cntA0 = cntA0 + 1;
	    }
            else
            {
                state = wait_hash_p;
            }
            break;
	case unlocked:
	    if (tempA == 0x80)
	    {
		state = locked;
		cntA7 = cntA7 + 1;
	    }
	    else
	    {
		state = wait_hash_p;
	    }
	    break;
	case locked:
	    state = wait_l;
	    break;
	case wait_l:
	    if (tempA == 0x80)
	    {
		state = wait_l;
	    }
	    else
	    {
		state = wait_hash_p;
	    }
	    break;
        default:
	    state = smstart;
	    break;
    }

    switch(state)
    {
        case smstart:
	    PORTB = 0x00;
        case wait_hash_p:
        case wait_hash_r:
	case wait_l:
        case wait_y:
	    break;
        case unlocked:
            PORTB = 0x01;
            break;
	case locked:
	    PORTB = 0x00;
	    break;
        default:
            break;
    }
}
int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    cntA0 = 0x00;
    cntA1 = 0x00;
    cntA2 = 0x00;
    cntA7 = 0x00;
    state = smstart;
    /* Insert your solution below */
    while (1) {
	Tick();
    }
    return 0;
}
