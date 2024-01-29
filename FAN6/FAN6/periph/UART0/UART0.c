#include "UART0.h"

uint8_t uart0RxBuff[100];
uint8_t uart0RxComplFlag;

void UART0_init()
{
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0); // TxD, RxD
	UCSR0A |= (1<<U2X0); // X2 Mode
	UBRR0L = 207; // BaudRate 9600
	UCSR0B |= (1<<RXCIE0); // Rx Interrupt
	uart0RxComplFlag = 0;
}
void UART0_Transmit( unsigned char data ) // Data Transmitter
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) )
	;
	/* Put data into buffer, sends the data */
	UDR0 = data;
}
unsigned char UART0_Receive( void ) // Data Receiver
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) )
	;
	/* Get and return received data from buffer */
	return UDR0;
}
uint8_t UART0_Avail()
{
	if(!(UCSR0A & (1<<RXC0))) return 0; // Rx data가 없다면 0
	return 1; // Rx data가 있다면 1
}
void UART0_print(char *str)
{
	for (int i=0; str[i]; i++)
	{
		UART0_Transmit(str[i]);
	}
}
void UART0_ISR_Process()
{
	static uint8_t uart0RxTail = 0;
	uint8_t rx0Data = UDR0;
	
	if (rx0Data == '\n')
	{
		uart0RxBuff[uart0RxTail] = rx0Data; // 개행까지 저장
		uart0RxTail++;
		uart0RxBuff[uart0RxTail] = 0; // NULL 저장
		uart0RxTail = 0; // Tail 초기화
		uart0RxComplFlag = 1; // 수신완료 Flag
	}
	else
	{
		uart0RxBuff[uart0RxTail] = rx0Data;
		uart0RxTail++;
	}
}

uint8_t UART0_getRxFlag()
{
	return uart0RxComplFlag;
}
void UART0_setRxFlag()
{
	uart0RxComplFlag = 1;
}
void  UART0_clearRxFlag()
{
	uart0RxComplFlag = 0;
}

uint8_t *UART0_getRxBuff()
{
	return uart0RxBuff;
}