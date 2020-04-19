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

enum States {Start, wait, seq1, seq2, doorUnlock, doorLock} state; 

unsigned char tmpA; //global variables 
unsigned char tmpB;//= 0x00; 
unsigned char tmpC; 

void Tick() {
	//unsigned char tmpA = PINA;
	switch(state) { //transitions
		case Start:
			tmpB = 0x00;
			state = wait;	
			break;
	
		case  wait:
			tmpC = 0x00;
			if ((tmpA & 0x04) == 0x04) { //If only PA2 is on, then go to start of sequence 
				state = seq1;
			}
			else if ((tmpA & 0x80) == 0x80) { //If PA7 is on, then lock the door (!PB0)
				state = doorLock;
			}
			else { 
				state = wait;
			}
			break;

		case seq1: //# pressed 
			tmpC = 0x01;
			if ((tmpA & 0x87) == 0x00) { //IF PA2 is released, then go to next part of sequence 
				state = seq2;
			}
			else if ((tmpA  & 0x87) == 0x04) { //If PA2 is still held down, stay in seq 2
				state = seq1; 
			}
			else { state = wait; }
			break;

		case seq2: //# released 
			tmpC = 0x02;
			if ((tmpA & 0x87) == 0x02) { //IF PA1 is turned on, then unlock the door 
				state = doorUnlock;
				tmpB = 1;	//was 0x01 originally AS IT SHOULD BE TEST
			}
			else if ((tmpA & 0x87) == 0x00) { //IF PA2 is still released 
				state = seq2;
			}
			else { state = wait; }
			break; 

		case doorUnlock: //Might have to wait for either button to be released 
			tmpC = 0x03;
			
			
			if ((tmpA & 0x02) == 0x02) { //If PA1 is still on, then stay 
				state = doorUnlock;
			}
			else if ((tmpA & 0x80) == 0x80) { //If PA7 is still on, then stay 
				state = doorUnlock;
			}
			else {//else just go back to wait state			
				state = wait;
			} 
			break;

		case doorLock: 
			tmpC = 0x04;

			if ((tmpA & 0x80) == 0x80) { //IF PA7 is still on, stay
				state = doorLock;
			}
			else {
				state = wait;
			}
			break;

		default: 
			//shouldn't go here
			tmpB = tmpB && 0xFF; //if it goes here, should output error
			state = Start;
			break;					
	}
	
	switch(state) { //Don't really need state actions
		case wait: break;
		case seq1: break;
		case seq2: break;
		case doorUnlock: break;
		case doorLock:
			tmpB = 0;
			break;		
		
		default:
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF; //Makes all As as input
	DDRB = 0xFF; PORTB = 0x00; //Makes all C pins as output	
	
	tmpB = 0x00;
	tmpC = 0x00;
	state = Start;  
	/* Insert your solution below */
    	while (1) {
		//read inputs
		tmpA = PINA; 

		Tick(); 
	
		//write output
		PORTB = tmpB;	//
		PORTC = tmpC;	
    	}
    	return 1;
}
