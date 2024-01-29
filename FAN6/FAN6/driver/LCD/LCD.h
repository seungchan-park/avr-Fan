#ifndef LCD_H_
#define LCD_H_
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "../../periph/I2C/I2C.h"

#define LCD_CONTROL_DDR DDRB
#define LCD_DATA_DDR DDRC
#define LCD_CONTROL_PORT PORTB
#define LCD_DATA_PORT PORTC
#define LCD_RS 5
#define LCD_RW 6
#define LCD_E 7
#define LCD_FUNCTION_SET 0x38
#define LCD_DISPLAY_OFF	 0x08
#define LCD_DISPLAY_CLEAR 0x01
#define LCD_ENTRY_MODE_SET 0x06
#define LCD_DISPLAY_ON	 0x0C

#define I2C_LCD_RS 0
#define I2C_LCD_RW 1
#define I2C_LCD_E 2
#define I2C_LCD_BACKLIGHT 3
#define I2C_LCD_SLA 0x27
#define I2C_LCD_SLA_W I2C_LCD_SLA<<1
#define LCD_4BIT_FUNCTION_SET 0x28

void Gpio_init();
void LCD_init();
void Gpio_writeControlData(uint8_t data);
void LCD_cmdMode();
void LCD_charMode();
void LCD_writeMode();
void LCD_enableHigh();
void LCD_enableLow();
void LCD_writeByte(uint8_t data);
void Gpio_writeData(uint8_t data);
void LCD_writeCmdData(uint8_t data);
void LCD_writeCharData(uint8_t data);
void LCD_writeString(char *str);
void LCD_gotoXY(uint8_t row, uint8_t col);
void LCD_displayClear();
void LCD_writeStringXY(uint8_t row, uint8_t col, char *str);

void I2C_LCD_init();
void I2C_LCD_cmdMode();
void I2C_LCD_charMode();
void I2C_LCD_writeMode();
void I2C_LCD_enableHigh();
void I2C_LCD_enableLow();
void I2C_LCD_writeByte(uint8_t data);
void I2C_LCD_writeCmdData(uint8_t data);
void I2C_LCD_writeCharData(uint8_t data);
void I2C_LCD_writeString(char *str);
void I2C_LCD_gotoXY(uint8_t row, uint8_t col);
void I2C_LCD_displayClear();
void I2C_LCD_writeStringXY(uint8_t row, uint8_t col, char *str);
void I2C_LCD_writeNibble(uint8_t data);
void I2C_LCD_sendToI2C(uint8_t sla_w, uint8_t data);
void I2C_LCD_backLightOff();
void I2C_LCD_backLightOn();

#endif /* LCD_H_ */