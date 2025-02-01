/*
 * D2-Lab012.c
 *
 * Created: 1/28/2025 10:14:28 AM
 * Author : samue
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "dig7seg/dig7seg.h"

volatile uint8_t inicio = 0;
uint8_t contador = 5;
uint8_t contador_j1 = 0;
uint8_t contador_j2 = 0;

void setup() {
	cli();
	
	DDRD |= 0xFF;
	PORTD = 0x00;
	
	//Declaracion de botones
	DDRC &= ~((1 << PC1) | (1 << PC2) | (1 << PC3));  // Botones como entrada
	PORTC |= (1 << PC1) | (1 << PC2) | (1 << PC3);   // Pull-ups activadas

	// LEDS DEL JUEGO
	DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB3) | (1 << PB4) | (1 << PB5);
	DDRC |= (1 << PC0);
	DDRD |= (1 << PD7);
	
	// INTERRUPCION
	PCICR |= (1 << PCIE1);
	PCMSK1 |= (1 << PC1);
	
	sei();
}

void actualizar_leds() {
	// JUGADOR 1
	PORTD = (PORTD & ~(1 << PD7)) | ((contador_j1 & (1 << 3)) ? (1 << PD7) : 0);
	PORTB = (PORTB & ~((1 << PB0) | (1 << PB1) | (1 << PB2))) | ((contador_j1 & 0x07) << PB0);
	
	// JUGADOR 2
	PORTB = (PORTB & ~((1 << PB3) | (1 << PB4) | (1 << PB5))) | ((contador_j2 & 0x07) << PB3);
	PORTC = (PORTC & ~(1 << PC0)) | ((contador_j2 & (1 << 3)) ? (1 << PC0) : 0);
}

void iniciar_juego() {
	while (contador > 0) {
		number7seg(contador);
		_delay_ms(1000);
		contador--;
	}
	contador = 5;
	number7seg(0);
	_delay_ms(100);

	while (contador_j1 < 15 && contador_j2 < 15) {
		if (!(PINC & (1 << PC2))) {
			_delay_ms(80);
			if (!(PINC & (1 << PC2))) {
				contador_j1++;
				actualizar_leds();
			}
		}
		if (!(PINC & (1 << PC3))) {
			_delay_ms(80);
			if (!(PINC & (1 << PC3))) {
				contador_j2++;
				actualizar_leds();
			}
		}
	}

	_delay_ms(500);
	if (contador_j1 >= 15) {
		number7seg(1);
		} else {
		number7seg(2);
	}

	_delay_ms(3000);
	contador_j1 = 0;
	contador_j2 = 0;
	actualizar_leds();
}

int main(void) {
	setup();
	
	while (1) {
		if (inicio) {
			iniciar_juego();
			inicio = 0;
		}
	}
}

ISR(PCINT1_vect) {
	_delay_ms(50);
	if (!(PINC & (1 << PC1))) {
		inicio = 1;
	}
}

