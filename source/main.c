/*	Author: agonz250
 *  Partner(s) Name: 028 
 *	Lab Section:
 *	Assignment: Lab # 4 Exercise # 2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, Wait, incHold, decHold, reset} state; 

unsigned char tmpA; //global variables 
unsigned char tmpB;//= 0x00; 

void Tick() {
	//unsigned char tmpA = PINA;
	switch(state) { //transitions
		case Start: 
			state = Arelease;
			break;
		
		case Wait:
			if ((tmpA & 0x01) == 0x01) {
				state = incHold;
			} 
			else if ((tmpA & 0x02) == 0x02)
			{
				state = decHold;
			}
			else if ((tmpA & 0x03) == 0x03) {
				state = reset;
			}
			else {
				state = Wait;
			}
			break;

		case incHold:
			if ((tmpA & 0x01) == 0x01) { 
				state = incHold;
			}
			else { 
				state = Wait;
			}			
			break;

		case decHold:
			if ((tmpA & 0x02) == 0x02) {
				state = decHold;
			}
			else {
				state = Wait;
			}
			break;

		case reset: 
			if ((tmpA & 0x03) == 0x03) {
				state = resset;
			}
			else {
				state = Wait;
			}
			break;

		default: 
			//shouldn't go here
			state = Start;
			break;					
	}

	switch(state) { 
		case Wait:

		case incHold:		
		default:
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF; //Makes all As as input
	DDRB = 0xFF; PORTB = 0x00; //Makes all B pins as output	
	
	//unsigned char tmpA;
	//unsigned char tmpB;
	tmpB = 0x00;
	state = Start;  
	/* Insert your solution below */
    	while (1) {
		//read inputs
		tmpA = PINA; 

		Tick(); 
	
		//write output
		PORTB = tmpB;		
    	}
    	return 1;
}
