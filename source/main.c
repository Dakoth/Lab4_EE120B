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

enum States {Start, wait, seq1, seq2, door} state; 

unsigned char tmpA; //global variables 
unsigned char tmpC;//= 0x00; 

void Tick() {
	//unsigned char tmpA = PINA;
	switch(state) { //transitions
		case Start:
			state = wait;	
			break;
	
		case  wait:
			if ((tmpA & 0x87) == 0x04) { //If only PA2 is on, then go to start of sequence 
				state = seq1;
			}
			else if ((tmpA & 0x87) == 0x80) { //If PA7 is on, then lock the door
				state = door;
				tmpB = 0x00;	//MIGHT HAVE TO CHANGE THIS 
			}
			else { 
				state = wait;
			}
			break;

		case seq1:
			if ((tmpA & 0x87) == 0x00) { //IF PA2 is released, then go to next part of sequence 
				state = seq2;
			}
			else { state = wait; }
			break;

		case seq2;
			if ((tmpA & 0x87) == 0x02) { //IF PA1 is turned on, then unlock the door 
				state = door;
				tmpB = 0x01;
			}
			else { state = wait; }
			break; 

		case door: 
			state = wait; 
			break;

		default: 
			//shouldn't go here
			state = Start;
			break;					
	}

	switch(state) { //Don't really need state actions
		
		
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
