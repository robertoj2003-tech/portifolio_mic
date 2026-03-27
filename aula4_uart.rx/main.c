/*
 * main.c
 *
 * Created: 3/27/2026 3:54:13 PM
 *  Author: Aluno
 */ 

#define F_CPU 16000000
#include <xc.h>
#include "util/delay.h"

uint8_t gReceivedBuffer [4];
void UART_receiveMessage(uint8_t * pBuffer, int pSize){
  
   uint8_t * tBufferPtr = pBuffer;
  for(int i=0; i<pSize; i++){
	while( (UCSR0A & (1<<RXC0)) == 0); //ESPERAR UMA MENSAGEM CHEGAR
	uint8_t tReceivedByte = UDR0;
	*tBufferPtr = tReceivedByte;
	tBufferPtr++;
}
	}

void UART_parsemessage(uint8_t *pMessage){
	 uint8_t tChecksum = 0;
	 for(int i=0; i<3; i++){
		 tChecksum += pMessage[i];
	 }
	 if(pMessage[3] == tChecksum) {
		PORTB |= (1<<PORTB0);
		} else {
		PORTB = (1<<PORTB2);
	}

}

//FUNÇÃO PRINCIPAL UART RX
int main(void)
{   
	DDRB = (1<<DDB0) |(1<<DDB1)|(1<<DDB2) ;
	UBRR0 = 103; // CONFIGURAR BAUD RATE PARA 9600
	UCSR0A = (0<<U2X0);
	UCSR0B = (1<<RXEN0) | (0<<UCSZ02); // HABILITA RECEPTOR
	UCSR0C = (0<<UMSEL01) | (0<<UMSEL00)  //MODO ASSINCRONO
	       | (1<<UPM01) | (0<<UPM00)// HABILIT PARIDADE PAR
	       | (0<<USBS0) // 1 BIT DE STOP
	       | (1<<UCSZ01) | (1<<UCSZ00); // FRAMES DE 8 BITS
    while(1)  {
	UART_receiveMessage(gReceivedBuffer, 4);
	UART_parsemessage(gReceivedBuffer);
	_delay_ms(200);
    }
}