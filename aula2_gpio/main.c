/*
 * main.c
 *
 * Created: 3/6/2026 2:36:36 PM
 *  Author: Roberto Paravizi 
 */ 

#define F_CPU 16000000
#include <xc.h>
#include "util/delay.h"


void atividade1()//piscar um led ligado ao pino PC2, enquanto a chave ligada ao pino PD3 estiver pressionada
{DDRC |= (1<<DDC2);   //configurar o pino PC2 como sa�da
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

void atividade2()	//controla 6 leds ligados a porta (PB0 a PB5) em uma logica de pinheirinho de natal
{
	DDRD &= (1<<DDD3);//configura pino PD3 como entrada
	DDRB |= (1<<DDB5)|(1<<DDB4)|(1<<DDB3)|(1<<DDB2)|(1<<DDB1)|(1<<DDB0); //conf pinos PN0-PB5 como saída
	uint8_t tState= 1; //guarda estado de acionamento dos LEDs
	while(1){ 
		tState = tState <<1;
		if(tState == 0b010000000)
		
		{
			tState = 1;
			}

		if(( PIND & (1<<PIND3)) !=0){//chave pressionada,  Ler o valor da chave PD3 (PODE SER 0b00001000)
	  PORTB = tState;
	  
	}else{
		//chave aberta
		PORTB = 0;
	}
_delay_ms(200);

	}
}


int main(void)
{
	atividade2()
}