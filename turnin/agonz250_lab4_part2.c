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
unsigned char tmpC;//= 0x00; 

void Tick() {
	//unsigned char tmpA = PINA;
	switch(state) { //transitions
		case Start:
			tmpC = 7; 
			state = Wait;
			break;
		
		case Wait:
			if ( ((tmpA & 0x01) == 0x01) && ((tmpA & 0x02) == 0x00) ) { //if PA0 && !PA1
				state = incHold;

				if (tmpC < 9) { ++tmpC; } //TRANSITION ACTION

			} 
			else if ( ((tmpA & 0x02) == 0x02) && ((tmpA & 0x01) == 0x00) ) //if PA1 && !PA0
			{
				state = decHold;

				if (tmpC > 0) { --tmpC; }	//TRANSITION ACTION

			}
			else if ((tmpA & 0x03) == 0x03) { //if PA1 && PA0
				state = reset;
				tmpC = 0;
			}
			else { //If none of the above
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
				state = reset;
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
			break;

		case incHold:
			//if (tmpC < 9) { ++tmpC; }
			break;
		
		case decHold:
			//if (tmpC > 0) { --tmpC; }
			break;
		
		case reset: 
			//tmpC = 0;
			break;
		default:
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF; //Makes all As as input
	DDRC = 0xFF; PORTC = 0x00; //Makes all C pins as output	
	
	tmpC = 0x00;
	state = Start;  
	/* Insert your solution below */
    	while (1) {
		//read inputs
		tmpA = PINA; 

		Tick(); 
	
		//write output
		PORTC = tmpC;		
    	}
    	return 1;
}
