/*
 * main.c
 *
 * Created: 5/8/2026 5:08:10 PM
 *  Author: Aluno
 */ 

#define F_CPU 16000000
#include "util/delay.h"
#include <xc.h>
#include "avr/interrupt.h"


uint8_t gTWIdata = 5;
ISR(TWI_vect){
	uint8_t tState  = (TWSR & 0b11111000);
	switch(tState){
		case 0x60:{
			gTWIdata = TWDR;
			TWCR = (1<<TWINT)| (1<<TWEA)|(1<<TWEN);
		}break;
		case 0xA8:{
			TWDR = gTWIdata;
		}break;
		
			default:{
				
			}break;
	}
	
	TWCR = (1<<TWINT) | (1<<TWEN);
}

 
void TWI_slave_config(){
	// DDRC = (1<<DDC4) | (1<<DDC5);
	TWBR = 12; //BIT RATE 400KHZ
	TWSR = (0<<TWPS1) | (0<<TWPS0); // PRESCALER=1
	TWAR = (0x55<<1);
	TWCR = (1<<TWEN) | (1<<TWIE);
	sei();
	
}

int main(void)
{
	TWI_slave_config();
	while(1)
	{
		
		//TODO:: Please write your application code
	}
}