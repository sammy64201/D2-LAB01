/*
 * dig7seg.c
 *
 * Created: 1/28/2025 10:18:49 AM
 *  Author: samue
 */ 


#include "dig7seg.h"

void number7seg(uint8_t number){
	
	switch (number){
	case 5:
		PORTD = (1 << PD6) | (1 << PD5) | (1 << PD3) | (1 << PD2) | (1 << PD1); // 5
		break;
	case 4:
		PORTD = (1 << PD6) | (1 << PD5) | (1 << PD2) | (1 << PD0);             // 4
		break;
	case 3:
		PORTD = (1 << PD5) | (1 << PD3) | (1 << PD2) | (1 << PD1) | (1 << PD0); // 3
		break;
	case 2:
		PORTD = (1 << PD5) | (1 << PD4) | (1 << PD3) | (1 << PD1) | (1 << PD0); // 2
		break;
	case 1:
		PORTD = (1 << PD0) | (1 << PD2);                                       // 1
		break;
	case 0:
		PORTD = (1 << PD6) | (1 << PD4) | (1 << PD3) | (1 << PD2) | (1 << PD1) | (1 << PD0); // 0
		break;
	default:
		PORTD = 0x00; // Apaga todos los LEDs si el valor es inválido
		break;
	}
	
}