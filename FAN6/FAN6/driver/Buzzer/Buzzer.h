#ifndef BUZZER2_H_
#define BUZZER2_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define BUZZER_ICR ICR3
#define BUZZER_OCR OCR3A
#define BUZZER_DDR DDRE
#define BUZZER_TCCRA TCCR3A
#define BUZZER_TCCRB TCCR3B
#define BUZZER_COM1 COM3A1
#define BUZZER_COM0 COM3A0
#define BUZZER_WGM3 WGM33
#define BUZZER_WGM2 WGM32
#define BUZZER_WGM1 WGM31
#define BUZZER_WGM0 WGM30
#define BUZZER_CS2 CS32
#define BUZZER_CS1 CS31
#define BUZZER_CS0 CS30

void Buzzer_init();
void Buzzer_makeHerz(uint16_t herz);
void Buzzer_soundOn();
void Buzzer_soundOff();
void Buzzer_powerOnSound();
void Buzzer_powerOffSound();
void Buzzer_Button1_Sound();
void Buzzer_Button2_Sound();
void Buzzer_Button3_Sound();


#endif /* BUZZER2_H_ */