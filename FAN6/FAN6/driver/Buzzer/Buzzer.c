
#include "Buzzer.h"

void Buzzer_init()
{
	// Timer/Counter3, Fast PWM Mode, Top ICR3, Duty Cycle OCR3A
	// Prescaler 1/64, Non-Inverting
	// Frequency 1kHz, DutyCycle 50% -> 목적
	
	TCCR3B |= ((1<<WGM33)|(1<<WGM32)); // 1110 WGM3~0 Fast PWM 14 Mode
	TCCR3A |= ((1<<WGM31)|(0<<WGM30)); // 1110 WGM3~0 Fast PWM 14 Mode
	
	TCCR3B |= ((0<<CS32)|(1<<CS31)|(1<<CS30)); // 1/64 prescaler
	
	BUZZER_DDR |= (1<<4);
}
void Buzzer_makeHerz(uint16_t herz)
{
	if (herz < 100) herz = 100;
	else if(herz > 4000) herz = 4000;
	BUZZER_ICR = (250000/herz) - 1; // 1ms period의 top값 설정
	OCR3B = BUZZER_ICR / 2; // Duty Cycle
}
void Buzzer_soundOn()
{
	TCCR3A |= ((1<<COM3B1)|(0<<COM3B0)); // Non-Inverting Mode
}
void Buzzer_soundOff()
{
	TCCR3A &= ~((1<<COM3B1)|(1<<COM3B0)); // Off
}
void Buzzer_powerOnSound()
{
	// 6옥타브 도미솔도
	Buzzer_soundOn();
	Buzzer_makeHerz(1046);
	_delay_ms(100);
	TCNT3 = 0;
	Buzzer_makeHerz(1318);
	_delay_ms(100);
	TCNT3 = 0;
	Buzzer_makeHerz(1567);
	_delay_ms(100);
	TCNT3 = 0;
	Buzzer_makeHerz(2093);
	_delay_ms(100);
	TCNT3 = 0;
	Buzzer_soundOff();
}

void Buzzer_powerOffSound()
{
	// 6옥타브 도솔미도
	Buzzer_soundOn();
	Buzzer_makeHerz(2093);
	_delay_ms(100);
	TCNT3 = 0;
	Buzzer_makeHerz(1567);
	_delay_ms(100);
	TCNT3 = 0;
	Buzzer_makeHerz(1318);
	_delay_ms(100);
	TCNT3 = 0;
	Buzzer_makeHerz(1046);
	_delay_ms(100);
	TCNT3 = 0;
	Buzzer_soundOff();
}

void Buzzer_Button1_Sound()
{
	Buzzer_soundOn();
	Buzzer_makeHerz(1046);
	_delay_ms(100);
	TCNT3 = 0;
	Buzzer_soundOff();
}

void Buzzer_Button2_Sound()
{
	Buzzer_soundOn();
	Buzzer_makeHerz(1318);
	_delay_ms(100);
	TCNT3 = 0;
	Buzzer_soundOff();
}

void Buzzer_Button3_Sound()
{
	Buzzer_soundOn();
	Buzzer_makeHerz(1567);
	_delay_ms(100);
	TCNT3 = 0;
	Buzzer_soundOff();
}


