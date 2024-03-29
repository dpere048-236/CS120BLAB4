/*	Author: David Perez dpere048@ucr.edu
 *  Partner(s) Name: 
 *	Lab Section: 022
 *	Assignment: Lab4 #  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
enum States{start, led1, wait, led0} state;
unsigned char button;
unsigned char tmpA;
void led_Tick(){
	switch(state){
	case start:
		if(button == 1){ //if button is pressed, state turns on led pb1
			state = led1;
		}
		else{ //if no button is pressed, remains in start
			state = start;
		}
		break;
	case led1:
		if(button == 1){
			state = led0;
		}
		else{
			state = wait;
		}
		break;
	case wait:
		if(button == 1){ //button pressed siwtches back to led0
			state = led0;
		}
		else{ 
			state = wait;
		}
		break;
	case led0:
		if(button == 1){
			state = led1; //switches leds
		}
		else{
			state = start; //stays at start
		}
		break;
	}
	switch(state){
		case start:
			tmpA = 0x01;
			break;
		case led1:
			tmpA = 0x02; //when ledpb1 is on, tmpA = 0x02
			break;
		case wait:
			tmpA = 0x02; //when waiting, tmpA is still 0x02
			break;
		case led0:
			tmpA = 0x01;  //when ld1  tmpA =is 0x01
			break;
	}
}


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF; //configure port A as inputs
	DDRB = 0xFF; PORTB = 0x00; //configure port B as outputs
	state = start; //state is in initial state
    /* Insert your solution below */
    while (1) {
	button = PINA&0x01;
	led_Tick();
	PORTB = tmpA;
	}

    return 1;
}
