﻿


#ifndef FND_H_
#define FND_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define FND_DIGIT_DDR		DDRG
#define FND_DATA_DDR		DDRF
#define FND_DIGIT_PORT		PORTG
#define FND_DATA_PORT		PORTF

#define FND_DIGIT_1			0
#define FND_DIGIT_2			1
#define FND_DIGIT_3			2
#define FND_DIGIT_4			3
#define FND_DP              10


void FND_init();
void FND_colonOn();
void FND_colonOff();
void FND_dispNum(uint16_t fndNum);
void FND_setFndData(uint16_t data);
void FND_ISR_Process();



#endif /* FND_H_ */