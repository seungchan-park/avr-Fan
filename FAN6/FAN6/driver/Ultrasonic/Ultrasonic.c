#include "Ultrasonic.h"

void Ultrasonic_ISR_Process()
{
	if(USOIC_PIN & (1<<USONIC_ECHO))
	{
		Ultrasonic_timerStart();
		Ultrasonic_switchInterrupt(FALLING_EDGE); //falling edge 확인 위해서 바꿈
	}
	else
	{
		Ultrasonic_timerStop();
		Ultrasonic_switchInterrupt(RISING_EDGE); //다시 신호 받기 위해서 바꿈
		Ultrasonic_setCompltFlag();
	}
}

void Ultrasonic_switchInterrupt(uint8_t mode)
{
	if(mode == FALLING_EDGE)
	{
		EICRA &= ~((1<<ISC21) | (1<<ISC20)); //초기화
		EICRA |= (1<<ISC21) | (0<<ISC20);
	}
	else
	{
		EICRA &= ~((1<<ISC21) | (1<<ISC20)); //초기화
		EICRA |= (1<<ISC21) | (1<<ISC20);
	}
}

void Ultrasonic_timerStart()
{
	USONIC_TCNT = 0;
	TCCR1B |= (0<<CS12) | (1<<CS11) | (1<<CS10); //prescaler 011 설정 , /64분주
}

void Ultrasonic_timerStop()
{
	TCCR1B &= ~((1<<CS12) | (1<<CS11) | (1<<CS10)); //prescaler 000 설정
}

void Ultrasonic_init()
{
	USONIC_DDR &= ~(1<<USONIC_ECHO); //echo pin
	USONIC_DDR |= (1<<USONIC_TRIG); //trigger pin
	
	//INT2
	EICRA |= (1<<ISC21) | (1<<ISC20) ; //rising edge interrupt
	EIMSK |= (1<<INT2);
	
	ultraSonicDistanceFlag = 0;
}

void Ultrasonic_trigger()
{
	USONIC_PORT |= (1<<USONIC_TRIG);
	_delay_us(10);
	USONIC_PORT &= ~(1<<USONIC_TRIG);
}

void Ultrasonic_setCompltFlag() //
{
	ultraSonicDistanceFlag = 1;
}

uint8_t Ultrasonic_getCompltFlag() //거리 측정 확인용
{
	return ultraSonicDistanceFlag;
}

void Ultrasonic_clearFlag() //다음 거리측정 위해서
{
	ultraSonicDistanceFlag = 0;
}

uint16_t Ultrasonic_getDistance()
{
	return USONIC_TCNT * 0.068;
}