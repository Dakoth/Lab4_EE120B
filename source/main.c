/*	Author: agonz250
 *  Partner(s) Name: 028 
 *	Lab Section:
 *	Assignment: Lab # 4 Exercise # 5
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, locked, correctButt, correctButtRelease, unlocked} state; 

unsigned char tmpA; //global variables 
unsigned char tmpB;//= 0x00; 
unsigned char tmpC; 
unsigned char array[4] = {0x04, 0x01, 0x02, 0x01};
unsigned char count = 0;

void Tick() {
	switch(state) { //transitions
		case Start:
			tmpB = 0;
			state = locked;	
			break;
		
		case locked:
			count = 0;

			if ((tmpA & 0x07) == 0x04) { //If # start checking sequence
				state = correctButt;
				++count;
			}
			else { 
				state = locked;
			}
			break;

		case correctButt: //A correct button in the sequence is held down
			if ((tmpA & 0x07) == array[count]) { //If correct button, go to next in sequence 
				state = correctButt;
			}
			else if ((tmpA & 0x07) == 0x00) { //IF a button is released, go to other state 
				++count;
				state = correctButtRelease;
			}
			else {				//if failed, go back to start 
				state = locked; 
				count = 0;
			}
		
			break;

		case correctButtRelease:
			if ((tmpA & 0x07) == 0x00) {
				state = correctButtRelease;
			}
			else if  ( (count == 3)&& (tmpA & 0x07) == array[count]) { //if reached correct end of sequence
				state = unlocked;
			}
			else if ((tmpA & 0x07) == array[count]) { //If inputted next button in sequence
				state = correctButt;
			}
			else { 
				state = locked;
				count = 0;
			}
			break;

		case unlocked: 
			if ((tmpA & 0x80) == 0x80) {
				count = 0;
				state = locked;
			}
			else { 
				state = unlocked; 
			}
			break;
		
		default: 
			state = Start;
			break;					
	}
	
	switch(state) { //Don't really need state actions
		case locked:
			tmpB = 0;
			tmpC = 0; 
			break;
		case correctButt:
			tmpC = 1; 
			break;
		case correctButtRelease: 
			tmpC = 2;
			break;

		case unlocked: 
			tmpB = 1;
			tmpC = 3;
			break;	

		default:
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF; //Makes all As as input
	DDRB = 0xFF; PORTB = 0x00; //Makes all B pins as output	
	DDRC = 0xFF; PORTC = 0x00; 
	
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
