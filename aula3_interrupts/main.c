/*
 * main.c
 *
 * Created: 3/13/2026 2:22:59 PM
 *  Author: Aluno
 */ 

#define F_CPU 16000000

#include <xc.h>
#include "avr/interrupt.h"
#include "util/delay.h"

int gPD2State = 0;
int gLedFlag = 0;
int gPD3State = 0;


ISR(INT0_vect) {
	gLedFlag=1;
}
ISR(INT1_vect){
	gLedFlag=1;
}
ISR(PCINT2_vect){
	if((PIND & (1<<PIND2)) !=0) {// SE PINO D2 ESTA NO NIVEL LOGICO ALTO
		if(gPD2State == 0) {
			gLedFlag = 1; }
			gPD2State =1;
	}else{
		//pino d2 esta no nivel logico baixo
		gPD2State = 0;
	}
	gLedFlag = 1;
	
	if((PIND & (1<<PIND3)) !=0) {// SE PINO D2 ESTA NO NIVEL LOGICO ALTO
		if(gPD3State == 0) {
		gLedFlag = 1; }
		gPD3State =1;
		}else{
		//pino d2 esta no nivel logico baixo
		gPD3State = 0;
	}
	gLedFlag = 1;
}

void EXTINT_config(){
		EICRA = (0<<ISC01)|(1<<ISC00)	// INT0: Ambas as bordas
		|(1<<ISC11)|(1<<ISC10);			 // INT1: NA BORDA DE SUBIDA
		EIMSK = (1<<INT1)|(1<<INT0);	// INT0 habilitada, INT1 desabilitada
}

void PCINT_config(){
	PCMSK2 |= (1<<PCINT18)|(1<<PCINT19); // HABILITA PCINT18 E PCINT19 (equivale pinos PD2 E)
	PCICR |= (1<<PCIE2); // HABILIDA GRUPO 2 (EQUIVALE PORTA D)
}
int main(void) {
	DDRC = (1<<DDC0);				// configura pino PC0 como saIda (LED)
	PCINT_config();
	sei();
    if(gLedFlag){
			PORTC = (1<<PORTC0); //Alterna LED
			_delay_ms(100);
			PORTC = 0;
	    }
}