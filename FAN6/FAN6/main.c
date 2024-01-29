#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>  // interrupt ó��
#include "ap/Fan6/FAN6.h"

ISR(TIMER0_OVF_vect)	// TIMER/Count0 Overflow Interrupt (1ms)
{
	FND_ISR_Process();	// FND ���
}

ISR(TIMER2_COMP_vect)	// TIMER/Count2 Compare Match Interrupt (1ms)
{
	TimeClock_decMilisec(); // Timer Clock
	TimeClock_incMilisec(); // Fan Clock
}

ISR(USART0_RX_vect)		// USART ���� �Ϸ� Interrupt
{
	UART0_ISR_Process();
}

ISR(INT2_vect) // �����ļ��� �� External Interrupt2
{
	Ultrasonic_ISR_Process();	// ������ ����
}


int main(void)
{
	sei();
	
	FAN6_init();
	while (1)
	{
		Fan6_excute();
	}
}

