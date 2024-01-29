#include "Motor.h"


void Motor_makeHerz(uint16_t herz)
{
	if(herz <100) herz = 100;
	else if(herz > 4000) herz = 4000;
	MOTOR_ICR = (250000/herz)-1; // herzHz
	MOTOR_OCR = MOTOR_ICR /2; // Duty cycle 50%
}

void Motor_makeHerzDuty(uint16_t herz, uint8_t duty)
{
	if(herz <100) herz = 100;
	else if(herz > 4000) herz = 4000;
	MOTOR_ICR = (250000/herz)-1; // herzHz
	MOTOR_OCR = MOTOR_ICR /duty; // Duty cycle 50%
}

void MotorOn()
{
	MOTOR_TCCRA |= ((1<<MOTOR_COM1)) | ((0<<MOTOR_COM2)); //Non_Inverting Mode
}

void MotorOff()
{
	MOTOR_TCCRA &= ~((1<<MOTOR_COM1)) | ((1<<MOTOR_COM2));
}

void Motor_init()
{
	//TIM3, FAST PWM Mode, Top ICR3, Duty Cycle OCR3A
	//PreScaler 1/64, Non_Inverting,
	//Frequency 1Khz, Duty Cycle 50%
	
	// 1110 WGM3~0 FAST PWM 14번 Mode
	MOTOR_TCCRB |= ((1<<MOTOR_WGM3)) | ((1<<MOTOR_WGM2));
	MOTOR_TCCRA |= ((1<<MOTOR_WGM1)) | ((0<<MOTOR_WGM0));
	
	//PreScaler 1/64
	MOTOR_TCCRB |= ((0<<MOTOR_CS2)) | ((1<<MOTOR_CS1))| ((1<<MOTOR_CS0));	
	MOTOR_DDR |= (1<<3);
}
