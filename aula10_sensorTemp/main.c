/*
 * main.c
 *
 * Target: ATmega328P (Arduino Uno na Bancada Datapool PIC-2377)
 * Frequência do Cristal: 16 MHz
 * Objetivo: Amostragem do LM35 (A0) a 4Hz via Auto-Trigger do Timer 1
 * Retorno: Serial UART a 9600 bps (8N1) com matemática protegida
 */ 

#define F_CPU 16000000UL 
#include <xc.h>
#include <avr/interrupt.h>

// Configuração do Baud Rate para a Serial (16MHz / (16 * 9600)) - 1 = 104
#define BAUD_PRESCALE 104

volatile float temperatura = 0.0;
volatile uint8_t nova_leitura = 0;

// --- FUNÇÕES DA SERIAL ---
void USART_Init(unsigned int ubrr) {
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    
    UCSR0B = (1 << TXEN0); // Habilita TX
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8N1
}

void USART_TxChar(char caractere) {
    while (!(UCSR0A & (1 << UDRE0))); 
    UDR0 = caractere;                 
}

void USART_TxString(const char* str) {
    while (*str) {
        USART_TxChar(*str++);
    }
}

// Função de envio puramente matemática e protegida contra estouros
void Enviar_Dados_Serial(float temp) {
    // Evita valores negativos espúrios causados por ruído
    if (temp < 0) temp = 0; 
    
    int parte_inteira = (int)temp;
    // Pega a primeira casa decimal
    int parte_decimal = (int)((temp - parte_inteira) * 10); 
    if (parte_decimal < 0) parte_decimal = -parte_decimal;

    // Isola cada dígito matematicamente
    char centena = (parte_inteira / 100) % 10;
    char dezena  = (parte_inteira / 10) % 10;
    char unidade = parte_inteira % 10;

    // Só imprime a centena se ela for maior que zero (evita mostrar "025.4 C")
    if (parte_inteira >= 100) {
        USART_TxChar(centena + '0');
    }
    
    // Só imprime a dezena se o número for maior ou igual a 10
    if (parte_inteira >= 10) {
        USART_TxChar(dezena + '0');
    }
    
    // Unidade sempre é impressa
    USART_TxChar(unidade + '0');
    
    // Ponto decimal
    USART_TxChar('.');
    
    // Parte decimal (garantida entre 0 e 9 pelo operador % 10)
    USART_TxChar((parte_decimal % 10) + '0');
    
    USART_TxString(" C\r\n");
}

// --- INTERRUPÇÃO DO ADC ---
ISR(ADC_vect) {
    uint16_t adc_raw = ADC;
    
    // Conversão matemática para o LM35
    temperatura = adc_raw * 0.48828125;
    
    nova_leitura = 1; 
    TIFR1 = (1 << OCF1B); // Limpa o flag do Timer 1
}

// --- FUNÇÃO PRINCIPAL ---
int main(void)
{
    USART_Init(BAUD_PRESCALE);
    USART_TxString("--- Monitor de Temperatura (4Hz) ---\r\n");

    // 1. CONFIGURAÇÃO DO ADC
    ADMUX = (1 << REFS0); // Referência AVCC (5V) e Canal A0
    ADCSRB = (1 << ADTS2) | (0 << ADTS1) | (1 << ADTS0); // Trigger pelo Timer 1 Compare Match B
    
    ADCSRA = (1 << ADEN)  |
             (1 << ADATE) |
             (1 << ADIE)  |
             (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Prescaler 128

    // 2. CONFIGURAÇÃO DO TIMER 1 (4Hz)
    TCCR1A = 0; 
    TCCR1B = (1 << WGM12) | (1 << CS12); // Modo CTC, Prescaler 256
    OCR1A = 15624; 
    OCR1B = 15624; 

    TIFR1 = (1 << OCF1B); 

    sei();

    while(1)
    {
        if (nova_leitura) {
            nova_leitura = 0; 
            Enviar_Dados_Serial(temperatura); 
        }
    }
}