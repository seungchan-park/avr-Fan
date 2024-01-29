#include "FAN6.h"

// Timer Clock 용 변수
uint16_t milisec;
uint8_t sec;
uint8_t min;
uint8_t timeState;
uint8_t timeleftState;

// Fan Clock 용 시간 함수
uint16_t Fan_milisec;
uint8_t Fan_sec;
uint8_t fanModeState;
uint8_t fanPowerState;

// FND ":" 을 위한 변수
uint16_t colon_time;

// LCD(I2C), LCD(gpio) display 용 buff
char buff[30];

// 초음파 센서용 변수
uint16_t distance;
uint8_t distance_backup_state = 0;

// UART
// UART printf 출력을 위한 선언 
// UART에 전달되는 데이터를 스트림 형태로 바꿔줘야 하기 때문에 객체를 생성할 수 있는 코드 추가필요 (입출력 객체 연결) ******** 설명 검토필요 (이해못했음..)

/*FILE OUPUT는 FDEV_SETUP_STREAM로 초기화 하는데, 인자로 put에는 UART_transmit, get에는 NULL, rwflag에는 _FDEV_SETUP_WRITE로 받는다.

출력으로 사용하겠다는 의미이다.

사용자가 정의한 버퍼를 stdio stream을 바꿔준다.

printf 함수는 stdio stream을 따르는 함수로 putchar()함수와 printf를 연결해주었다고 이해하면 된다. */

FILE OUT = FDEV_SETUP_STREAM(UART0_Transmit, NULL, _FDEV_SETUP_WRITE); 


// --------------- Time synchronization --------------- // 함수 선언

void TimeClock_incMilisec()		// FAN auto mode 용 시간 증가 함수
{
	Fan_milisec = (Fan_milisec + 1) % 1000; // 1ms마다 milisec증가 범위: 0 ~ 999
	if (Fan_milisec) return; // milisec이 0이면 999까지 돌고 1000이 된것이므로 (거짓)
	
	Fan_sec = (Fan_sec + 1) % 60;
	if (Fan_sec) return;
}

void TimeClock_decMilisec()		// Timer Clock 의 시간 감소 함수
{
	milisec = (milisec +1) % 1000;
	if((milisec % colon_time) < (colon_time)/2) FND_colonOn();
	else FND_colonOff();
	
	if(milisec) return;
	
	if(sec == 0) sec = 60;		// sec = 0 이면 60초로 변경
	sec = (sec - 1) % 60;
	if(!(sec == 59)) return;	// sec 이 0 - > 59 일 때만 밑의 min = min -1 실행
	
	min = (min - 1) % 60;
	if(min) return;
}


// ---------------           FAN         --------------- // 함수 선언

void FAN_init()
{
	Buzzer_init();
	Buzzer_powerOnSound();
	UART0_init();
	stdout = &OUT;
	//TIM2_init(); // 시간계산 interrupt
	I2C_LCD_init();
	Motor_init();
	Button_init(&btnMode, &DDRA, &PINA, 0);
	Button_init(&btnChange, &DDRA, &PINA, 1);
	fanModeState = CHANGE;
	fanPowerState = OFF;
	Fan_milisec = 0;
	Fan_sec = 0;
}

void FAN_excute()
{
	FAN_eventCheck();
	FAN_run();
}

void FAN_eventCheck()		// Button 0 press 확인 및 Fan mode 변경
{
	switch(fanModeState)
	{
		case CHANGE:
		if (Button_GetState(&btnMode)==ACT_RELEASED)
		{
			Buzzer_Button1_Sound();
			fanModeState = AUTO;
			Fan_milisec = 0;
			Fan_sec = 0;
		}
		break;
		case AUTO:
		if (Button_GetState(&btnMode)==ACT_RELEASED)
		{
			Buzzer_Button1_Sound();
			fanModeState = CHANGE;
		}
		break;
	}
}

void FAN_run()		// Fan mode(CHANGE, AUTO)에 맞는 출력 실행
{
	switch(fanModeState)
	{
		case CHANGE:
		FAN_change();
		FAN_changeUART0();
		FAN_active();
		break;
		case AUTO:
		FAN_auto();
		FAN_active();
		break;
	}
}

void FAN_change()	// Button 1 press 확인 및 Fan change 모드일때 풍량 변경
{
	switch(fanPowerState)
	{
		case OFF:
		if (Button_GetState(&btnChange)==ACT_RELEASED)
		{
			Buzzer_Button2_Sound();
			fanPowerState = LOW;
			I2C_LCD_displayClear(); // 버튼을 누르면 I2C LCD에 있는 데이터 초기화
		}
		break;
		case LOW:
		if (Button_GetState(&btnChange)==ACT_RELEASED)
		{
			Buzzer_Button2_Sound();
			fanPowerState = MIDDLE;
			I2C_LCD_displayClear();
		}
		break;
		case MIDDLE:
		if (Button_GetState(&btnChange)==ACT_RELEASED)
		{
			Buzzer_Button2_Sound();
			fanPowerState = HIGH;
			I2C_LCD_displayClear();
		}
		break;
		case HIGH:
		if (Button_GetState(&btnChange)==ACT_RELEASED)
		{
			Buzzer_Button2_Sound();
			fanPowerState = OFF;
			I2C_LCD_displayClear();
		}
		break;
	}
	
}

void FAN_changeUART0() // UART0로 문자열을 입력받으면 풍량 변경
{
	uint8_t *rxString = UART0_getRxBuff();
	if (UART0_getRxFlag())
	{
		UART0_clearRxFlag();
		if (!(strcmp((char*)rxString,"OFF\n"))) // strcmp 문자열이 같다면 0
		{
			fanPowerState = OFF;
			if(fanPowerState == OFF)
			{
				printf("OFF\n");
			}
			I2C_LCD_displayClear();
		}
		else if (!(strcmp((char*)rxString,"LOW\n")))
		{
			fanPowerState = LOW;
			if(fanPowerState == LOW)
			{
				printf("LOW\n");
			}
			I2C_LCD_displayClear();
		}
		else if (!(strcmp((char*)rxString,"MIDDLE\n")))
		{
			fanPowerState = MIDDLE;
			if(fanPowerState == MIDDLE)
			{
				printf("MIDDLE\n");
			}
			I2C_LCD_displayClear();
		}
		else if (!(strcmp((char*)rxString,"HIGH\n")))
		{
			fanPowerState = HIGH;
			if(fanPowerState == HIGH)
			{
				printf("HIGH\n");
			}
			I2C_LCD_displayClear();
		}
	}
}

void FAN_auto() // 자동모드
{
	if (Fan_sec == 3) // 3초마다 풍량조절
	{
		fanPowerState++;
		Fan_sec = 0; // 풍량이 조절되면 0초로 초기화
		I2C_LCD_displayClear();
	}
	if (fanPowerState == 4) // HIGH MODE에서 LOW MODE로 변화
	{
		fanPowerState = 1;
	}
}

void FAN_active()	// 수동모드
{
	switch(fanPowerState)
	{
		case OFF:
		MotorOff();
		I2C_display();
		break;
		case LOW:
		MotorOn();
		Motor_makeHerzDuty(1000, 5);
		I2C_display();
		break;
		case MIDDLE:
		MotorOn();
		Motor_makeHerzDuty(1000, 3);
		I2C_display();
		break;
		case HIGH:
		MotorOn();
		Motor_makeHerzDuty(1000,1);
		I2C_display();
		break;
	}
}

void FAN_changeOff()		// TimerClock의 남은 time이 0이 되었을때 Fan 종료 함수
{
	if ((timeleftState == END) && (timeState == 1))
	{
		fanPowerState = OFF;
		fanModeState = CHANGE;
		timeState = 0;
		I2C_LCD_displayClear();
		Buzzer_powerOffSound();
	}
}



// ---------------           TimerClock         --------------- // 함수 선언

void TimeClock_init()
{
	sec	= 0;
	min	= 0;
	colon_time = 1000;
	timeleftState = END;
	LCD_init();
	FND_init();
	TIM0_init();
	TIM2_init();
	Button_init(&btnTime, &BUTTON_DDR, &BUTTON_PIN, 2);
}

void TimeClock_execute()
{
	TimeClock_eventCheck();
	TimeClock_Run();
	TimeClockFind_OFF();
	FAN_changeOff();
}

void TimeClock_eventCheck()		// Button 2 press 확인 및 Time 변경
{
	switch(timeleftState)
	{
		case OFF:
		if(Button_GetState(&btnTime) == ACT_RELEASED)
		{
			Buzzer_Button3_Sound();
			timeleftState = ONEMINUTE;		// 다음 Timerleftstate로 변경
			TimeClockButton_run();			// Time 값 적용
			timeState = 1;					// Timer 작동중 표시
		}
		break;
		case LOW:
		if(Button_GetState(&btnTime) == ACT_RELEASED)
		{
			Buzzer_Button3_Sound();
			timeleftState = THREEMiNUTE;
			TimeClockButton_run();
			timeState = 1;
		}
		break;
		case MIDDLE:
		if(Button_GetState(&btnTime) == ACT_RELEASED)
		{
			Buzzer_Button3_Sound();
			timeleftState = FIVEMINUTE;
			TimeClockButton_run();
			timeState = 1;
		}
		break;
		case HIGH:
		if(Button_GetState(&btnTime) == ACT_RELEASED)
		{
			Buzzer_Button3_Sound();
			timeleftState = END;
			TimeClockButton_run();
			timeState = 0;
		}
		break;
	}
}

void TimeClockButton_run()	// Timer mode state 에 맞는 Time 값 적용 함수
{
	switch(timeleftState)
	{
		case END:
		milisec = 0;
		sec = 0;
		min = 0;
		break;
		
		case ONEMINUTE:
		milisec = 0;
		sec = 0;
		min = 1;
		break;
		
		case THREEMiNUTE:
		milisec = 0;
		sec = 0;
		min = 3;
		break;
		
		case FIVEMINUTE:
		milisec = 0;
		sec = 0;
		min = 5;
		break;
	}
}



void TimeClock_Run()		// FND + LCD(gpio) 의 Timer 값 표시
{
	FND_dispMinSec();
	LCD_dispMinSec();
}


void TimeClockFind_OFF()			// TimerClock의 남은 시간 == 0 이면, Timerclock 0으 fix하는 함수
{
	if((sec == 0) && (min == 0))
	{
		timeleftState = END;
		TimeClockButton_run();
	}
}



// ---------------           LCD(I2C)         --------------- // 함수 선언

void I2C_display()			// LCD(I2C) timer 표시
{
	switch(fanPowerState)
	{
		case OFF:
		sprintf(buff, "FAN6");
		I2C_LCD_writeStringXY(0, 3, buff);
		sprintf(buff, "OFF");
		I2C_LCD_writeStringXY(1, 3, buff);
		break;
		case LOW:
		sprintf(buff, "FAN6");
		I2C_LCD_writeStringXY(0, 3, buff);
		sprintf(buff, "LOW_MODE");
		I2C_LCD_writeStringXY(1, 3, buff);
		break;
		case MIDDLE:
		sprintf(buff, "FAN6");
		I2C_LCD_writeStringXY(0, 3, buff);
		sprintf(buff, "MIDDLE_MODE");
		I2C_LCD_writeStringXY(1, 3, buff);
		break;
		case HIGH:
		sprintf(buff, "FAN6");
		I2C_LCD_writeStringXY(0, 3, buff);
		sprintf(buff, "HIGH_MODE");
		I2C_LCD_writeStringXY(1, 3, buff);
		break;
	}
}


// ---------------           LCD(gpio)         --------------- // 함수 선언

void LCD_dispMinSec()		 // LCD(gpio) timer 표시
{
	//char buff[30];
	sprintf(buff, "THE FAN6");
	LCD_writeStringXY(0,3,buff);
	sprintf(buff, "Time : %02d:%02d", min,sec);
	LCD_writeStringXY(1,2,buff);
}



// ---------------             FND             --------------- // 함수 선언

void FND_dispMinSec()			// FND timer 표시
{
	uint16_t timeClockData;
	
	timeClockData = (min * 100) + sec;
	FND_setFndData(timeClockData);
}



// ---------------        초음파 센서             --------------- // 함수 선언

void Ultrasonic_execute()
{
	Ultrasonic_trigger();			// 초음파 발사
	if(Ultrasonic_getCompltFlag()) //flag 1일때
	{
		static uint8_t before_fanModeState;
		static uint8_t before_fanPowerState;
		Ultrasonic_clearFlag(); // flag 다시 0으로 세팅
		distance= Ultrasonic_getDistance();
		
		uint8_t dis_result = ultrasonic_distance_case(distance);
		
		switch(dis_result)
		{
			case Closed:
			if(distance_backup_state == 0 )		// 초음파 센서의 거리가 0이 된적이 없을 때만 Fan mode backup
			{
				before_fanModeState = fanModeState;
				before_fanPowerState = fanPowerState;
				fanModeState = CHANGE;
				fanPowerState = OFF;		
				distance_backup_state = 1;				// backup 을 했음을 나타내는 상태
				I2C_LCD_displayClear();
				Fan_milisec =0;		
				Fan_sec =0;	
			}
			break;
			
			case Far:
			if(distance_backup_state == 1)				// fanMode가 backup 된적 있을 때만 이전 Fan mode 원복
			{
				fanModeState = before_fanModeState;
				fanPowerState = before_fanPowerState;
				distance_backup_state = 0;
			}
			break;
		}
	}
}

uint8_t ultrasonic_distance_case(uint16_t data)			// 초음파 센서 거리 10cm 이내인지 확인 함수
{
	if (data < 10) return Closed;
	else return Far;
}


// ---------------           최종 FAN6             --------------- // 함수 선언

void FAN6_init()
{
	Ultrasonic_init();
	TimeClock_init();
	FAN_init();
}

void Fan6_excute()
{
	Ultrasonic_execute();
	TimeClock_execute();
	FAN_excute();
}