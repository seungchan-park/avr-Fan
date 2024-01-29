#include "Timer.h"


void TIM0_init()  // 1ms Overflow Interrupt , Display
{
	TCCR0 |= (1<< CS02) | (0<< CS01) | (1<<CS00); // 128 Prescaler
	TIMSK |= (1<<TOIE0); // TIMSK Timer/Counter0 Overflow Interrupt Enable
	TCNT0 = 130;
}

void TIM2_init() // 1ms CTC mode Interrupt , time
{
	TCCR2 |= ((0<<CS22) | (1<<CS21) | (1<<CS20));	// 1/64
	TCCR2 |= ((1<<WGM21) | (0 << WGM20));			// CTC Mode
	TIMSK |= (1<<OCIE2); // OutCompare Interrupt Enable
	OCR2 = 250 - 1;
}