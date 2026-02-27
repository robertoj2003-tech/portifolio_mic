

#include <xc.h>
#include "GPIO.h"
#include "USART.h"


int main(void)
{
	GPIO_initialize();
	GPIO_blinkLed();
    while(1)
    {
		USART_initialize();
		 USART_send();
        //TODO:: Please write your application code 
    }
}