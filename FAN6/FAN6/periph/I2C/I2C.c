#include "I2C.h"

void I2C_init()
{
	I2C_DDR |= (1<<I2C_SCL) | (I2C_SDA);
	TWBR = 72; //100khz SCL
	TWSR = 0; //slave mode 아님.
}



//1byte 송신
void I2C_txByte(uint8_t SLA_W, uint8_t data) //data 보내는 함수
{
	I2C_start(); //1. Start bit
	I2C_txDevAddr(SLA_W); //2.SLA+R/W 8bit + 1bit ARK
	I2C_txData(data); //3. 1byte data 송신
	I2C_stop(); //4. Stop bit
}

void I2C_start() //1. Start bit
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); //Send START condition
	while (!(TWCR & (1<<TWINT))); // TWINT flag 설정될 때까지 기다려라
}
void I2C_txDevAddr(uint8_t SLA_W) //2.SLA+R/W 8bit + 1bit ARK
{
	TWDR = SLA_W;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
}
void I2C_txData(uint8_t data) //3. 1byte data 송신
{
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
}
void I2C_stop() //4. Stop bit
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}