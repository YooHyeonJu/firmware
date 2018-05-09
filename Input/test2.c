#include "LPC1768_fnd.h"
#include "LPC1768_utility.h"

int Led_Count = 0;



int main(void)
{
	FND_Init();
	EXTI_Init();
	Led_Init(LED_ALL);
	AF_ConfigPin(GPIO_PORT_2,PINSEL_PIN_10,PINSEL_FUNC_1);
	
	EXTI_ConfigPin(EXTI_EINT0);
	//LPC_SC->EXTMODE = 0x0;
	//LPC_SC->EXTPOLAR = 0x0;
	NVIC_EnableIRQ(EINT0_IRQn);
	
	while(1)
	{
		Led_All_On();
		Delay(SEC_1/2);
		Led_All_Off();
		FND_COM_DATA_Select(8,Led_Count%10);
		Delay(SEC_1/2);
	}
}

void EINT0_IRQHandler(void)
{
	EXTI_ClearEXTIFlag(EXTI_EINT0);
	Led_Count++;
}
