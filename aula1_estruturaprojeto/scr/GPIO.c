#include "GPIO.h"
#include <xc.h>

void GPIO_initialize(){
	DDRB = (1<<DDB0);    //configura o pino PB0 como saida
}
void GPIO_blinkLed(){
	PORTB = (1<<PORTB0);  //aciona o pino
}