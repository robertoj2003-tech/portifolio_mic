/*
 * main.c
 *
 * Created: 6/12/2026 2:01:53 PM
 *  Author: Aluno
 */ 

#include <xc.h>
const float VREF = 1.1f; // ref interna de 1,1V

const float coeff_a[3] = { 1.000, -1.414, 1.000};
const float coeff_b[3] = { 1.000, -1.279, 0.810};
	
float x[3];
float y[3];

ISR(ADC_vect){
	uint16_t tADCValue = ADC;
	x[2]=x[1];
	x[1]=x[0];
	x[0]= VREF * ((float)tADCValue /1.024);   //saida em miliVolts do adc
	y[2]=y[1];
	y[1]=y[0];
	y[0] = coeff_a[0] * x[0] + coeff_a[1] * x[1] + coeff_a[2] * x[2]
	 + coeff_b[1] * y[1] +coeff_b[2] * y[2];
	
	//jogar resultado no PWM como saída
	OCR1A = (uint16_t)(y[0]* 65355);
}
	
int main(void)
{
    while(1)
    {
        //TODO:: Please write your application code 
    }
}