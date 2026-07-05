/*
 * main.c
 *
 * Created: 5/15/2026 2:49:47 PM
 *  Author: ROberto Paravizi
 */ 

#define F_CPU 8000000
#include <xc.h>
#include "avr/interrupt.h"
#include "util/delay.h"

uint8_t gPWM = 0;

int main(void) {
	DDRD = (1<<DDD6)|(1<<DDD5);
	TCCR0A = (1<<COM0A1)|(0<<COM0A0)	//OC0A PWM não-inversor
			|(1<<COM0B1)|(0<<COM0B0)	//OC0B PWM não-inversor
			|(1<<WGM01)|(1<<WGM00);		//Modo Fast PWM (modo 7) com TOP=OCR0A
	TCCR0B = (1<<WGM02)|(0<<CS02)|(1<<CS01)|(0<<CS00); //Prescaler de 8
	OCR0A  = 99; //período de 100 us
    while(1) {
        gPWM++;
		if(gPWM>99) gPWM=0;
        OCR0B  = gPWM;
		_delay_ms(10);
    }
}