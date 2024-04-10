//***************************************************************************
// Universidad del Valle de Guatemala
// IE2023: Programación de Microcontroladores
// Autor: Diego Cardona
// Hardware: ATMEGA328P
// Created: 09/04/2024
//***************************************************************************
// PreLab 4
//***************************************************************************
#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

unsigned char ButtonLastState_1 = 1;
unsigned char ButtonState_1 = 1;
unsigned char ButtonLastState_2 = 2;
unsigned char ButtonState_2 = 1;

int contador = 0;
int main(void)
{
	// salidas
	DDRD = 0xFF;
	PORTD = 0;
	// PINES RX TX
	UCSR0B = 0;
	// entradas
	DDRB &= ~(1<<0);
	PORTB |= (1<<PB0);
	DDRB &= ~(1<<1);
	PORTB |= (1<<PB1);
	// INTERRUPCION PARA PUERTO B
	PCICR |= (1<<PCIE0);
	// HABILITAR PARA PCINT0
	PCMSK0 |= ((1<<PCINT0)|(1<<PCINT1));
	sei();
	while (1)
	{
		if (contador > 255){
			contador = 0;
		}
		if (contador < 0){
			contador = 255;
		}
		PORTD = contador;
	}
}

ISR(PCINT0_vect){
	ButtonState_1 = PINB&(1<<PINB0);
	ButtonState_2 = PINB&(1<<PINB1);
	if ((ButtonState_1 == 0)&&(ButtonLastState_1 == 1)){
		ButtonLastState_1 = 0;
		contador ++;
	}
	if (ButtonState_1 == 1){
		ButtonLastState_1 = 1;
	}
	if ((ButtonState_2 == 0)&&(ButtonLastState_2 == 2)){
		ButtonLastState_2 = 0;
		contador --;
	}
	if (ButtonState_2 == 2){
		ButtonLastState_2 = 2;
	}
}
