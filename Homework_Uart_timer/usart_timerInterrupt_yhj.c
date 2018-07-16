#include "LPC1768_utility.h"
#include "debug_frmwrk.h"
#include "lpc17xx_timer.h"
#include "LPC17xx.H"
#include "lpc17xx_adc.h"



#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define LED_ONOFF 0x01
#define LED_ALT 0x02
#define LED_SHIFT 0x04
#define STX 0x02
#define ETX 0x03
void Printf(char *fmt, ...);


void TIMER0_Config(void);

int i,j;
int flag = 0;
int arr_index = 0;
int res_index = 0;
char buffer[100] = "";
uint16_t adc_value;

TIM_TIMERCFG_Type TIM_ConfigStruct;
TIM_MATCHCFG_Type TIM_MatchConfigStruct;

void Led_all_on(void)
{
	for(i = 0;i<3;i++)
	{
		Led_All_On();
		
	}
	Printf("OK\r\n");
}

void Led_all_off(void)
{
	for(i = 0;i<3;i++)
	{
		Led_All_Off();
	}
	Printf("OK\r\n");
}

void Start_Adc(void)
{
	char adc_buffer[20] = "adc=0x";
	
	ADC_StartCmd(LPC_ADC,ADC_START_NOW);
	
	TIM_MatchConfigStruct.MatchValue = 10000;
	
	TIM_ResetCounter(LPC_TIM0);
	TIM_Cmd(LPC_TIM0,ENABLE);
	
	UARTPuts(LPC_UART0,"ADC value on channel 2: ");
	UARTPutDec16(LPC_UART0,adc_value);
	UARTPuts(LPC_UART0,"\r\n");
	Delay(SEC_1);
	Printf("OK\r\n");
}



void Printf(char *fmt, ...)
{
   va_list    arg_ptr;
   uint8_t    i,len;
   char    sText[128];
      
   for (i = 0; i < 128; i++)
      sText[i] = 0;

   va_start(arg_ptr, fmt);
   vsprintf(sText, fmt, arg_ptr);
   va_end(arg_ptr);

   len = strlen(sText);
   for (i = 0; i < len; i++){
      UARTPutChar(LPC_UART0,sText[i]);
   }
}

void check()
{
	
	
	if(strcmp(buffer,"LED_ALL_ON") == 0)
	{
		Led_All_On();
		
		
	}
	if(strcmp(buffer,"LED_ALL_OFF") == 0)
	{
		Led_All_Off();
		
		
	}
	if(strcmp(buffer,"START_ADC") == 0)
	{
		Start_Adc();
		
	}
	if(strcmp(buffer,"STOP_ADC") == 0)
	{
		//Led_shift(2);
		
	}
	
}

int main(void)
{
	
	uint8_t menul[] = "final exam 201601781_yhj\n";
	/*
	"Baud_Rate : 9600\n"
	"Databits : 8\n"
	"Parity : 0\n"
	"Stopbits : 2\n\r";
	
	
	*/
	Led_Init(LED_ALL);
	
	
	UART_CFG_Type UARTConfigStruct;
	
	AF_ConfigPin(GPIO_PORT_0, PINSEL_PIN_2,PINSEL_FUNC_1);	//	P0.2
	AF_ConfigPin(GPIO_PORT_0, PINSEL_PIN_3,PINSEL_FUNC_1);	//	P0.3
	
	UART_ConfigStructInit(&UARTConfigStruct);
	UARTConfigStruct.Baud_rate = 9600;
	UARTConfigStruct.Databits = UART_DATABIT_8;
	UARTConfigStruct.Parity	= UART_PARITY_NONE;
	UARTConfigStruct.Stopbits = UART_STOPBIT_2;
	UART_Init((LPC_UART_TypeDef *)LPC_UART0, &UARTConfigStruct);
	UART_TxCmd((LPC_UART_TypeDef *)LPC_UART0, ENABLE);		
	UART_IntConfig(LPC_UART0,UART_INTCFG_RBR,ENABLE);
	
	UARTPuts(LPC_UART0,menul);
	UARTPuts(LPC_UART0,"\n");
	UARTPuts(LPC_UART0,"Baud_Rate : ");
		UARTPutDec16(LPC_UART0,UARTConfigStruct.Baud_rate);
		UARTPuts(LPC_UART0,"\n");
		UARTPuts(LPC_UART0,"Databits : ");
		UARTPutDec16(LPC_UART0,UARTConfigStruct.Databits);
		UARTPuts(LPC_UART0,"\n");
		UARTPuts(LPC_UART0,"Parity : ");
		UARTPutDec16(LPC_UART0,UARTConfigStruct.Parity);
		UARTPuts(LPC_UART0,"\n");
		UARTPuts(LPC_UART0,"Stopbits : ");
		UARTPutDec16(LPC_UART0,UARTConfigStruct.Stopbits);
		UARTPuts(LPC_UART0,"\n");
	
	
	NVIC_EnableIRQ(UART0_IRQn);
	
	
	TIMER0_Config();
	TIM_Init(LPC_TIM0,TIM_TIMER_MODE,&TIM_ConfigStruct);
	TIM_ConfigMatch(LPC_TIM0,&TIM_MatchConfigStruct);
	NVIC_EnableIRQ(TIMER0_IRQn);
	
	AF_ConfigPin(GPIO_PORT_0, PINSEL_PIN_25, PINSEL_FUNC_1);
	
	ADC_Init(LPC_ADC,200000);
	ADC_IntConfig(LPC_ADC,ADC_ADINTEN2,ENABLE);
	ADC_ChannelCmd(LPC_ADC,ADC_CHANNEL_2,ENABLE);
	NVIC_EnableIRQ(ADC_IRQn);
	
	while(1)
	{
		TIM_MatchConfigStruct.MatchValue = 300;
		if(flag == 1)
		{
			UARTPuts(LPC_UART0,buffer);
			check();
			Printf("\r\n");
			flag = 0;
			arr_index = 0;
			memset(buffer,0,sizeof(buffer));
		}
		
	}
}

void UART0_IRQHandler(void)
{
	TIM_ResetCounter(LPC_TIM0);
	buffer[arr_index] = UART_ReceiveByte(LPC_UART0);
	arr_index++;
	TIM_Cmd(LPC_TIM0,ENABLE);
}

void TIMER0_IRQHandler(void)
{
	TIM_ClearIntPending(LPC_TIM0,TIM_MR0_INT);
	flag = 1;
	TIM_Cmd(LPC_TIM0,DISABLE);
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
	TIM_MatchConfigStruct.MatchValue = 300;
}

void ADC_IRQHandler(void)
{
	if(ADC_ChannelGetStatus(LPC_ADC,ADC_CHANNEL_2,ADC_DATA_DONE))
	{
		ADC_ChannelCmd(LPC_ADC,ADC_CHANNEL_2,DISABLE);
		adc_value = ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_2);
		NVIC_DisableIRQ(ADC_IRQn);
		NVIC_EnableIRQ(ADC_IRQn);
		ADC_ChannelCmd(LPC_ADC,ADC_CHANNEL_2,ENABLE);
	}
		
}