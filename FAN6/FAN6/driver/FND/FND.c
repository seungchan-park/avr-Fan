#include "FND.h"

uint16_t fndData = 0;
uint8_t fndcolonFlag = 0;

void FND_init()
{
	FND_DIGIT_DDR |= ((1<<FND_DIGIT_4) | (1<<FND_DIGIT_3) | (1<< FND_DIGIT_2) | (1<<FND_DIGIT_1));
	FND_DATA_DDR = 0xff;
}

void FND_colonOn()
{
	fndcolonFlag = 1;
}

void FND_colonOff()
{
	 fndcolonFlag = 0;
}


void FND_dispNum(uint16_t fndNum)
{
	uint8_t fndFont[11]={0x3f, 0x06, 0x5B, 0x4F, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x67, 0x80};
	static uint8_t fndDigitState = 0;
	
	fndDigitState = (fndDigitState + 1)%5;
	
	FND_DIGIT_PORT |= ((1<<FND_DIGIT_1) | (1<<FND_DIGIT_2) | (1<<FND_DIGIT_3) | (1<<FND_DIGIT_4)); // FND Off
	
	switch (fndDigitState)
	{
		case 0 :
		FND_DATA_PORT = fndFont[fndNum/1000%10];
		FND_DIGIT_PORT &= ~(1<<FND_DIGIT_1);   // 천의자리 ON
		//_delay_ms(1);
		break;
		case 1 :
		FND_DATA_PORT = fndFont[fndNum/100%10];
		FND_DIGIT_PORT &= ~(1<<FND_DIGIT_2);   // 백의자리 ON
		//_delay_ms(1);
		break;
		case 2 :
		FND_DATA_PORT = fndFont[fndNum/10%10];
		FND_DIGIT_PORT &= ~(1<<FND_DIGIT_3);    // 십의자리 ON
		//_delay_ms(1);
		break;
		case 3 :
		FND_DATA_PORT = fndFont[fndNum%10];
		FND_DIGIT_PORT &= ~(1<<FND_DIGIT_4);     // 일의자리 ON
		//_delay_ms(1);
		break;
		case 4:
		if(fndcolonFlag) FND_DATA_PORT = fndFont[FND_DP];
		else FND_DATA_PORT = 0x00;
		FND_DIGIT_PORT &= ~(1<<FND_DIGIT_2);     // colon
		//_delay_ms(1);
		break;
	}
}

void FND_setFndData(uint16_t data)
{
	fndData = data;
}

void FND_ISR_Process()
{
	FND_dispNum(fndData);
}
