/*
 * main.c
 *
 * Created: 5/8/2026 3:58:01 PM
 *  Author: Roberto
 */ 
#define F_CPU 16000000
#include "util/delay.h"
#include <xc.h>


void TWI_master_config(){
    // DDRC = (1<<DDC4) | (1<<DDC5);
	TWBR = 12; //BIT RATE 400KHZ 
	TWSR = (0<<TWPS1) | (0<<TWPS0); // PRESCALER=1
	TWCR = (1<<TWEN);
	
}

void TWI_master_write_byte(uint8_t pAdress, uint8_t pData){
	//ENVIAR COND DE START
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN); // ENVIAR COND DE START
	while((TWCR & (1<<TWINT)) == 0); // esperar conclusão
	
	TWDR = (pAdress<<1) | 0; //1 para leitura e 0 para escrita
	TWCR = (1<<TWINT)|(1<<TWEN);
	
	while((TWCR & (1<<TWINT)) == 0); // esperar conclusão
	
	
	uint8_t tState = TWSR & 0b11111000;
	
	switch(tState){
		case 0x18: break; //ack recebido
		case 0x20: break; //nenhum ack recebido
		default: break;//outros erros
		
	}
	
	TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
}

int main(void)
{
	TWI_master_config();
	_delay_ms(1000);
    while(1)
    {
		TWI_master_write_byte(0X55, 'a');
		_delay_ms(1000);
        //TODO:: Please write your application code 
    }
}