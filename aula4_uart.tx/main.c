/*
 * main.c
 *
 * Created: 3/27/2026 1:54:19 PM
 *  Author: Aluno
 */ 
#define F_CPU 16000000
#include <xc.h>
 #include "util/delay.h"
 uint8_t gMessage[4]= {200,100,50,94}; //ultimo byte é checksum


int main(void)
{
	UBRR0 = 103; // CONFIGURAR BAUD RATE PARA 9600
	UCSR0A = (0<<U2X0);
	UCSR0B = (0<<TXEN0) | (0<<UCSZ02); // HABILITA TRANSMISSOR
	UCSR0C = (0<<UMSEL01) | (0<<UMSEL00)  //MODO ASSINCRONO
	| (1<<UPM01) | (0<<UPM00)// HABILIT PARIDADE PAR
	| (0<<USBS0) // 1 BIT DE STOP
	| (1<<UCSZ01) | (1<<UCSZ00); // FRAMES DE 8 BITS
	
    while(1)
    { 
		for(int i=0; i<4; i++)
		{
		UDR0 = gMessage[i];
			_delay_ms(2);

    }
	_delay_ms(10);
         }
}