#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define USONIC_DDR  DDRD
#define USONIC_PORT PORTD
#define USOIC_PIN   PIND
#define USONIC_TRIG 3
#define USONIC_ECHO 2
#define USONIC_TCNT TCNT1

uint8_t ultraSonicDistanceFlag;

enum{FALLING_EDGE,RISING_EDGE};

void Ultrasonic_ISR_Process();
void Ultrasonic_switchInterrupt(uint8_t mode);
void Ultrasonic_timerStart();
void Ultrasonic_timerStop();
void Ultrasonic_init();
void Ultrasonic_trigger();
void Ultrasonic_setCompltFlag();
uint8_t Ultrasonic_getCompltFlag();
void Ultrasonic_clearFlag();
uint16_t Ultrasonic_getDistance();

#endif /* ULTRASONIC_H_ */