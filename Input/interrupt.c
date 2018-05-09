#include "LPC1768_utility.h"

uint8_t Led_Count = 1;

int main(void)
{
	EXTI_Init();
	Led_Init(LED_ALL);
	AF_ConfigPin(GPIO_PORT_2,PINSEL_PIN_10,PINSEL_FUNC_1);
	
	EXTI_ConfigPin(EXTI_EINT0);
	//LPC_SC->EXTMODE = 0x0;
	//LPC_SC->EXTPOLAR = 0x0;
	NVIC_EnableIRQ(EINT0_IRQn);
	
	while(1)
	{
		Delay(SEC_1/10);
		if(Led_Count>8)
		{
			Led_Count = 1;
		}
		Led_On(Led_Count);
	}
}

void EINT0_IRQHandler(void)
{
	EXTI_ClearEXTIFlag(EXTI_EINT0);
	Led_Count++;
	Led_All_Off();
}
