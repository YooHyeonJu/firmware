#include "LPC1768_utility.h"
#include "LPC17xx.h"

int main(void)
{
	GPIO_SetDir(GPIO_PORT_1,GPIO_PIN_28,OUTPUT);
	GPIO_ClearValue(GPIO_PORT_1,GPIO_PIN_28);
	
	while(1)
	{
		GPIO_SetValue(GPIO_PORT_1,GPIO_PIN_28);
		Delay(SEC_1/2);
		GPIO_ClearValue(GPIO_PORT_1,GPIO_PIN_28);
		Delay(SEC_1/2);
	}
}