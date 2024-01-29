#ifndef BUZZER_H_
#define BUZZER_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define MOTOR_ICR  ICR3
#define MOTOR_OCR  OCR3A
#define MOTOR_DDR  DDRE
#define MOTOR_TCCRA TCCR3A
#define MOTOR_TCCRB TCCR3B
#define MOTOR_COM1  COM3A1
#define MOTOR_COM2  COM3A0
#define MOTOR_WGM3   WGM33
#define MOTOR_WGM2   WGM32
#define MOTOR_WGM1   WGM31
#define MOTOR_WGM0   WGM30
#define MOTOR_CS2   CS32
#define MOTOR_CS1   CS31
#define MOTOR_CS0   CS30

void Motor_makeHerz(uint16_t herz);
void Motor_makeHerzDuty(uint16_t herz, uint8_t duty);
void MotorOn();
void MotorOff();
void Motor_init();

#endif /* BUZZER_H_ */