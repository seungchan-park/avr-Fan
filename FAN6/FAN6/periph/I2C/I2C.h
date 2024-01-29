#ifndef I2C_H_
#define I2C_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define I2C_DDR DDRD
#define I2C_SCL 0
#define I2C_SDA 1

void I2C_init();
void I2C_txByte(uint8_t SLA_W, uint8_t data);
void I2C_start();
void I2C_txDevAddr(uint8_t SLA_W);
void I2C_txData(uint8_t data);
void I2C_stop();



#endif /* I2C._H_ */