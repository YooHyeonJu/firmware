#include "LPC1768_fnd.h"
#include "lpc17xx_timer.h"
#include "LPC1768_utility.h"

uint8_t time_10m = 0;
uint8_t time_1m = 0;
uint8_t time_10s = 0;
uint8_t time_1s = 0;

uint8_t lap_time_10m = 0;
uint8_t lap_time_1m = 0;
uint8_t lap_time_10s = 0;
uint8_t lap_time_1s = 0;

void TIMER0_Config(void);

TIM_TIMERCFG_Type TIM_ConfigStruct;
TIM_MATCHCFG_Type TIM_MatchConfigStruct;


int main(void)
{
	FND_Init();
	
	TIMER0_Config();
	TIM_Init(LPC_TIM0,TIM_TIMER_MODE,&TIM_ConfigStruct);
	TIM_ConfigMatch(LPC_TIM0,&TIM_MatchConfigStruct);
	NVIC_EnableIRQ(TIMER0_IRQn);
	TIM_Cmd(LPC_TIM0,ENABLE);
	
	while(1)
	{
		FND_COM_DATA_Select(8,time_1s);
		Delay(5000);
		FND_COM_DATA_Select(7,time_10s);
		Delay(5000);
		FND_COM_DATA_Select(6,time_1m);
		Delay(5000);
		FND_COM_DATA_Select(5,time_10m);
		Delay(5000);
	}
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

void TIMER0_IRQHandler(void)
{
	TIM_ClearIntPending(LPC_TIM0,TIM_MR0_INT);
	
	time_1s++;
	if(time_1s == 10)
	{
		time_10s++;
		time_1s = 0;
	}
	
	if(time_10s == 6)
	{
		time_1m++;
		time_10s = 0;
	}
	
	if(time_1m == 10)
	{
		time_10m++;
		time_1m = 0;
	}
	
	if(time_10m == 6)
	{
		time_10m = 0;
		time_1m = 0;
		time_10s = 0;
		time_1s = 0;
	}
}