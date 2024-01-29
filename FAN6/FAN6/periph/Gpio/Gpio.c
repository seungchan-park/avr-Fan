#include "Gpio.h"

void Gpio_initPort( volatile uint8_t *DDR  , uint8_t dir )
{
	if(dir == OUTPUT)
	{
		*DDR = 0xff;		// DDR port OUTPUT
	}
	else
	{
		*DDR = 0x00;		// DDR port INPUT
	}	
}

void Gpio_initPin(volatile uint8_t *DDR, uint8_t pinNum, uint8_t dir)
{
	if(dir == OUTPUT)
	{
		*DDR |= (1<<pinNum);  // pinNum OUTPUT
	}
	else
	{
		*DDR &= ~(1<<pinNum); // pinNum INPUT
	}
	
	
}
void Gpio_writePort(volatile uint8_t *PORT, uint8_t data)
{
	*PORT = data ;
}

void Gpio_writePin(volatile uint8_t *PORT, uint8_t pinNum, uint8_t state)
{
	if(state == GPIO_PIN_SET)
	{
		*PORT |= (1<<pinNum);
	}
	else
	{
		*PORT &= ~(1<<pinNum);
	}
}

uint8_t Gpio_readPort(volatile uint8_t *PIN)
{
	return *PIN;
}

uint8_t Gpio_readPin(volatile uint8_t *PIN , uint8_t pinNum)
{
	return ((*PIN & (1 << pinNum)) != 0);	 
}