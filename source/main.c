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
unsigned char tmpB;//= 0x00; 

void Tick() {
	//unsigned char tmpA = PINA;
	switch(state) { //transitions
		case Start:
			tmpB = 0x00;
			state = wait;	
			break;
	
		case  wait:
			if ((tmpA & 0x87) == 0x04) { //If only PA2 is on, then go to start of sequence 
				state = seq1;
			}
			else if ((tmpA & 0x87) == 0x80) { //If PA7 is on, then lock the door (!PB0)
				//if (tmpB > 0) {
				//	--tmpB;
				//}
				//tmpB = 0;
				tmpB = tmpB & 0x00;
				state = door;
			}
			else { 
				state = wait;
			}
			break;

		case seq1: //# pressed 
			if ((tmpA & 0x87) == 0x00) { //IF PA2 is released, then go to next part of sequence 
				state = seq2;
			}
			else if ((tmpA  & 0x87) == 0x04) { //If PA2 is still held down, stay in seq 2
				state = seq1; 
			}
			else { state = wait; }
			break;

		case seq2: //# released 
			if ((tmpA & 0x87) == 0x02) { //IF PA1 is turned on, then unlock the door 
				state = door;
				tmpB = tmpB & 0x01;	//was 0x01 originally AS IT SHOULD BE TEST
			}
			else if ((tmpA & 0x87) == 0x00) { //IF PA2 is still released 
				state = seq2;
			}
			else { state = wait; }
			break; 

		case door: //Might have to wait for either button to be released 
			if ((tmpA & 0x87) == 0x02) { //If PA1 is still on, then stay 
				state = door;
			}
			else if ((tmpA & 0x87) == 0x80) { //If PA7 is still on, then stay 
				state = door;
			}
			else {//else just go back to wait state			
				state = wait;
			} 
			break;

		default: 
			//shouldn't go here
			state = Start;
			break;					
	}

	switch(state) { //Don't really need state actions
		case wait: break;
		case seq1: break;
		case seq2: break;
		case door: break;		
		
		default:
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF; //Makes all As as input
	DDRB = 0xFF; PORTB = 0x00; //Makes all C pins as output	
	
	tmpB = 0x00;
	state = Start;  
	/* Insert your solution below */
    	while (1) {
		//read inputs
		tmpA = PINA; 

		Tick(); 
	
		//write output
		PORTB = tmpB;	//	
    	}
    	return 1;
}
