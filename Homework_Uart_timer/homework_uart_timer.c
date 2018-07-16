#include "LPC1768_utility.h"
#include "debug_frmwrk.h"
#include "lpc17xx_timer.h"
#include "LPC17xx.H"


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define LED_ONOFF 0x01
#define LED_ALT 0x02
#define LED_SHIFT 0x04
#define STX 0x02
#define ETX 0x03



void TIMER0_Config(void);

int i,j;
int flag = 0;
int arr_index = 0;
int res_index = 0;
char buffer[100] = "";

TIM_TIMERCFG_Type TIM_ConfigStruct;
TIM_MATCHCFG_Type TIM_MatchConfigStruct;

void Led_all_on_off(void)
{
	for(i = 0;i<3;i++)
	{
		Led_All_On();
		Delay(SEC_1/2);
		Led_All_Off();
		Delay(SEC_1/2);
	}
}

void Led_on_off_alt(int num)
{
   for(i=0;i<num;i++)
   {
      Led_All_Off();
      Led_On(LED1);
      Led_On(LED3);
      Led_On(LED5);
      Led_On(LED7);
      Delay(SEC_1/8);
      Led_All_Off();
      Led_On(LED2);
      Led_On(LED4);
      Led_On(LED6);
      Led_On(LED8);
      Delay(SEC_1/8);
      Led_All_Off();
   }
}

void Led_shift(int num)
{
   for(i=0;i<num;i++)
   {
      for(j=1;j<=8;j++)
      {
         Led_On(j);
         Delay(SEC_1/8);
         Led_Off(j);
      }
      for(j=8;j>=1;j--)
      {
         Led_On(j);
         Delay(SEC_1/8);
         Led_Off(j);
      }
   }
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

/*
void data_parsing()
{
	for(i = 0;i<sizeof(buffer);i++)
	{
		if(i > strlen(buffer)+10)
		{
			break;
		}
		
		if(buffer[i]==LED_ONOFF)
		{
			Led_all_on_off();
			UARTPutChar(LPC_UART0,buffer[i]);
		}   
		else if(buffer[i]==LED_ALT)
		{
			Led_on_off_alt(3);
		}
		else if(buffer[i]==LED_SHIFT)
		{
			Led_shift(3);
		}
	}
}
*/

void check()
{
	
	
	if(strcmp(buffer,"Led_all_on_off") == 0)
	{
		Led_all_on_off();
	}
	if(strcmp(buffer,"Led_on_off_alt") == 0)
	{
		Led_on_off_alt(2);
	}
	if(strcmp(buffer,"Led_shift") == 0)
	{
		Led_shift(2);
	}
	/*
	if(buffer[0]>=0 || buffer[0]<9)
	{
		data_parsing();
	}
	*/
}

int main(void)
{
	
	uint8_t menul[] = "final exam 201601781_yhj\r\n"
	"Baud_Rate : 9600\n"
	"Databits : 8\n"
	"Parity : 0\n"
	"Stopbits : 2\n\r";
	
	
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
	
	
	NVIC_EnableIRQ(UART0_IRQn);
	
	
	TIMER0_Config();
	TIM_Init(LPC_TIM0,TIM_TIMER_MODE,&TIM_ConfigStruct);
	TIM_ConfigMatch(LPC_TIM0,&TIM_MatchConfigStruct);
	NVIC_EnableIRQ(TIMER0_IRQn);
	
	while(1)
	{
		if(flag == 1)
		{
			UARTPuts(LPC_UART0,buffer);
			check();
			//Printf("\r\n");
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