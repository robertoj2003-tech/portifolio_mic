/*
 * main.c
 *
 * Created: 3/13/2026 2:23:03 PM
 *  Author: Aluno
 */ 

#define F_CPU 16000000
#include <xc.h>
#include "avr/interrupt.h"
#include "util/delay.h"

ISR(INT0_vect){
	PORTC ^= (1<<PORTC0); // ALTERNA LED
	_delay_ms(100);
	PORTC =0;
}

int main(void)
{
	DDRC = (1<<DDC0); // CONF PINO PC0 COMO SAIDA(LED)
	EICRA= (1<<ISC01)|(1<<ISC00); // borda de subida INT0
	EIMSK= (1<<INT1)|(1<<INT0); // ou 0b00000011 INT0 HABILITADA . INT1 DESABILITADA
	sei();
    while(1)
    {
        //TODO:: Please write your application code 
    }
}