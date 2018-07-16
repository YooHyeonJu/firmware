#include "LPC1768_utility.h"
#include "debug_frmwrk.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#define LED_ONOFF 0x01
#define LED_ALT 0x02
#define LED_SHIFT 0x04
#define STX 0x02
#define ETX 0x03
int i=0;
int j=0;
int decode=0;
int sint_flag=0;
uint8_t _command=0;
void Led_on_off_alt(int num)
{
   for(i=0;i<num;i++)
   {
      Led_All_Off();
      Led_On(LED1);
      Led_On(LED3);
      Led_On(LED5);
      Led_On(LED7);
      Delay(SEC_1/2);
      Led_All_Off();
      Led_On(LED2);
      Led_On(LED4);
      Led_On(LED6);
      Led_On(LED8);
      Delay(SEC_1/2);
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
         Delay(SEC_1/2);
         Led_Off(j);
      }
      for(j=8;j>=1;j--)
      {
         Led_On(j);
         Delay(SEC_1/2);
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
void hex_command(uint8_t cd)
{
   if(cd==LED_ONOFF)
		{
      Led_All_On();
      Delay(SEC_1/2);
      Led_All_Off();
   }   
   else if(cd==LED_ALT)
   {
      Led_on_off_alt(3);
   }
   else if(cd==LED_SHIFT)
   {
      Led_shift(3);
   }
   else
   {
      Printf("Invalid Command\n");
   }
}

int main(void)
{
   Led_Init(LED_ALL);
   Uart0_Init();
   NVIC_EnableIRQ(UART0_IRQn);
   UART_IntConfig(LPC_UART0,UART_INTCFG_RBR,ENABLE);
   while(1)
   {
      if(sint_flag)
      {
         hex_command(_command);
         sint_flag=0;
         _command=0;
      }
   }
}
void UART0_IRQHandler(void)
{
   uint8_t _usart_rcv=0;
   
   _usart_rcv = UART_ReceiveByte(LPC_UART0);
   UART_SendByte(LPC_UART0,_usart_rcv);
   
   if(decode == 0 &&_usart_rcv == STX)
   {
      decode=1;
   }
   else if(decode == 1)
   {
      _command = _usart_rcv;
      decode=2;
   }
   else if(decode==2)
   {
      if(_usart_rcv==ETX)
      {
         sint_flag=1;
      }
      else
      {
         Printf("RX Error\n");
      }
      decode=0;
   }
}