#ifndef UART0_H_
#define UART0_H_
#include <avr/io.h>

void UART0_init();
void UART0_Transmit( unsigned char data );
unsigned char UART0_Receive( void );
uint8_t UART0_Avail();
void UART0_print(char *str);
void UART0_ISR_Process();
uint8_t UART0_getRxFlag();
void UART0_setRxFlag();
void  UART0_clearRxFlag();
uint8_t *UART0_getRxBuff();

#endif /* UART0_H_ */