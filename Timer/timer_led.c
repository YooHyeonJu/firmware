#include "lpc17xx_timer.h"
#include "LPC1768_utility.h"

//Private variables
uint8_t Led_Status = 0;

//Private function
void TIMER0_Config(void);

//Private struct
TIM_TIMERCFG_Type TIM_ConfigStruct;
TIM_MATCHCFG_Type TIM_MatchConfigStruct;

int main(void)
{
	Led_Init(LED_ALL);
	
	TIMER0_Config();
	
	TIM_Init(LPC_TIM0,TIM_TIMER_MODE,&TIM_ConfigStruct);
	TIM_ConfigMatch(LPC_TIM0,&TIM_MatchConfigStruct);
	NVIC_EnableIRQ(TIMER0_IRQn);
	TIM_Cmd(LPC_TIM0,ENABLE);
	
	while(1)
	{
		if(Led_Status>9)
		{
			Led_All_Off();
			Led_Status = 1;
		}
	}
}

void TIMER0_IRQHandler(void)
{
	TIM_ClearIntPending(LPC_TIM0,TIM_MR0_INT);
	Led_On(Led_Status);
	Led_Status++;
}

void TIMER0_Config(void)
{
	TIM_ConfigStruct.PrescaleOption = TIM_PRESCALE_USVAL;
	TIM_ConfigStruct.PrescaleValue = 100;
	TIM_MatchConfigStruct.MatchChannel = 0;
	TIM_MatchConfigStruct.IntOnMatch = ENABLE;
	TIM_MatchConfigStruct.ResetOnMatch = ENABLE;
	TIM_MatchConfigStruct.StopOnMatch = DISABLE;
	TIM_MatchConfigStruct.ExtMatchOutputType = TIM_EXTMATCH_NOTHING;
	TIM_MatchConfigStruct.MatchValue = 10000;
}