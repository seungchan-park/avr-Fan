#ifndef FAN6_H_
#define FAN6_H_
#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include "../../driver/Button/Button.h"
#include "../../driver/FND/FND.h"
#include "../../periph/Timer/Timer.h"
#include "../../driver/LCD/LCD.h"
#include "../../driver/Motor/Motor.h"
#include "../../periph/UART0/UART0.h"
#include "../../driver/Ultrasonic/Ultrasonic.h"
#include "../../driver/Buzzer/Buzzer.h"

// Button 사용을 위한 구조체 선언
button_t btnMode, btnChange, btnTime;


// Timer Clock 남은 시간 조건값	
enum{END, ONEMINUTE, THREEMiNUTE, FIVEMINUTE};	


// FAN 조건값
enum{OFF, LOW, MIDDLE, HIGH}; // FAN 출력 세기

enum{CHANGE, AUTO};	//	FAN 출력 모드


//초음파 센서 거리 결과 조건값
enum {Closed, Far};


// 초음파 센서 함수
uint8_t ultrasonic_distance_case(uint16_t data);
void Ultrasonic_execute();


// Timer 용 함수
void TimeClock_init();
void TimeClock_execute();
void TimeClock_eventCheck();
void TimeClock_Run();
void TimeClockButton_run();
void TimeClockFind_OFF();

// Time synchronization 용 함수
void TimeClock_incMilisec();
void TimeClock_decMilisec();

// FAN 용 함수
void FAN_init();
void FAN_excute();
void FAN_eventCheck();
void FAN_run();
void FAN_change();
void FAN_changeUART0();
void FAN_auto();
void FAN_active();
void FAN_changeOff();

// LCD(I2C) 용 함수
void I2C_display();

// LCD(gpio) 용 함수
void LCD_dispMinSec();

// FND 용 함수
void FND_dispMinSec();

// 최종 FAN6 함수
void FAN6_init();
void Fan6_excute();

#endif /* FAN6_H_ */