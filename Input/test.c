#include "LPC1768_utility.h"
#include "LPC1768_fnd.h"

uint8_t Led_Count = 1;


int main(void)
{
	EXTI_Init();
	FND_Init();
	AF_ConfigPin(GPIO_PORT_2,PINSEL_PIN_10,PINSEL_FUNC_1);
	
	EXTI_ConfigPin(EXTI_EINT0);
	NVIC_EnableIRQ(EINT0_IRQn);
	
	while(1)
	{
		Delay(SEC_1/10);
		/*
		if(Led_Count>16)
		{
			Led_Count = 0;
		}
		*/
		FND_COM_DATA_Select(8,Led_Count%16);
		Delay(5000);
	}
}

void EINT0_IRQHandler(void)
{
	EXTI_ClearEXTIFlag(EXTI_EINT0);
	Led_Count++;
	//Led_All_Off();
}


