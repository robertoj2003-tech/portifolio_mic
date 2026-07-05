/*
 * main.c
 *
 * Created: 4/24/2026 3:49:53 PM
 *  Author: Roberto Junior
 */ 

#define F_CPU 16000000
#define SPI_BUFFER_SIZE 4

#include <xc.h>
#include "util/delay.h"
#include "spi.h"

uint8_t gTransmitBuffer[SPI_BUFFER_SIZE] = {1, 2, 3, 4};
uint8_t gReceiveBuffer[SPI_BUFFER_SIZE];

int main(void) {
	SPI_config();
    while(1) {
		SPI_transceiveBuffer(gTransmitBuffer, gReceiveBuffer, SPI_BUFFER_SIZE);
        _delay_ms(100);
    }
}