#define F_CPU 16000000
#include "GPIO.h"
#include <xc.h>
#include "util/delay.h"

void GPIO_initialize(){
	DDRB = (1<<DDB0);    //configura o pino PB0 como saida
}
void GPIO_blinkLed(){
	PORTB |= (1<<PORTB0);  //aciona o pino
	_delay_ms(300);
	PORTB &= ~(1<<PORTB0); 
	_delay_ms(700);
}