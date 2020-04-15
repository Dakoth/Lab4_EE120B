/*	Author: agonz250
 *  Partner(s) Name: 028 
 *	Lab Section:
 *	Assignment: Lab # 4 Exercise # 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, Arelease, Bhold, Brelease, Ahold} state; 

unsigned char tmpA; //global variables 
unsigned char tmpB; 


void Tick() {
	switch(Start) { //transitions
		case Start: //beginnning state
			state = Arelease;
			break;
		
		case Arelease: //
			if (tmpA == 0x01) { state = Bhold;	} 	
			else { state = Arelease; }
			break;

		case Bhold: 
			if (tmpA == 0x01) { state = Bhold; }	
			else { state = Brelease; }
			break;
		
		case Brelease: 
			if (tmpA == 0x01) { state = Ahold; }
			else { state = Brelease; }
			break;

		case Ahold:
			if (tmpA == 0x01) { state = Ahold;}
			else { state = Arelease; }
			break; 

		default: 
			//shouldn't go here
			break;					
	}

	switch(state) { 
		case Arelease:
			tmpB = 0x01; break; //!A1 A0

		case Bhold:
			tmpB = 0x02; break; //A0 !A0

		case Brelease:
			tmpB = 0x02; break; //A0 !A0

		case Ahold:
			tmpB = 0x01; break; //!A1 A0
		
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
	state = Start;  
	/* Insert your solution below */
    	while (1) {
		//read inputs
		tmpA = PORTA; 

		Tick(); 
	
		//write output
		PORTB = tmpB;		
    	}
    	return 1;
}
