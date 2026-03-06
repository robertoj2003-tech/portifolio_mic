/*
 * main.c
 *
 * Created: 3/6/2026 2:36:36 PM
 *  Author: Roberto Paravizi 
 */ 

#define F_CPU 16000000
#include <xc.h>
#include "util/delay.h"
/* O que esse cod faz:
*piscar um led ligado ao pino PC2, enquanto a chave 
*ligada ao pino PD3 estiver pressionada
*/
int main(void)
{
	DDRC |= (1<<DDC2);   //configurar o pino PC2 como saída
	DDRD &= (1<<DDD3);//configura pino PD3 como entrada
    while(1)
    {
       if(( PIND & (1<<PIND3)) !=0){//ler o valor da chave PD3 (PODE SER 0b00001000)
	   //chave pressionada
	   _delay_ms(300);
	   PORTC |= (1<<PORTC2); // acende
	   _delay_ms(700);
	  PORTC &= ~(1<<PORTC2); //apaga
	}else{
		//chave aberta
		PORTC &= ~(1<<PORTC2);
	}
    }
}