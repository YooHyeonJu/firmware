#include "LPC1768_fnd.h"
#include "lpc17xx_timer.h"
//#include "LED.H"
#include "Keypad.H" 
#include "LPC1768_utility.h"
#include "LPC17xx.H"
#include "lpc17xx_adc.h"
#include "debug_frmwrk.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

char rcv_buff[100] = {0}; // ÀÔ·ÂÇÑ °ªÀ» ¹ÞÀ» ¹öÆÛ
int idx = 0;
int flag = 0;
uint16_t adc_value = 0;


// -----------------------------------LED----------------------------------------------
// -----------------------------------FND----------------------------------------------

// -----------------------------------SW_INT-------------------------------------------
void EINT0_IRQHandler(void)
{
   EXTI_ClearEXTIFlag(EXTI_EINT0);
   
}


// -----------------------------------KEYPAD-------------------------------------------
void Keypad_test(){
  uint8_t Keypad_Value=0;
   Keypad_DIR_Input();
  Keypad_Value = Keypad('C');
   Delay(5000);
   EXT_IO_B_CS();
   FND_Init();
   //FND_COM_DATA_Select(8,Keypad_Value%10);
   //Delay(5000);
   //FND_COM_DATA_Select(7,Keypad_Value/10);
  
}


// -----------------------------------TIMER--------------------------------------------

void TIMER0_Config(void); // timer ¼³Á¤

TIM_TIMERCFG_Type TIM_ConfigStruct;            // ÇÁ¸®½ºÄÉÀÏ ¿É¼Ç ¹× °ª
TIM_MATCHCFG_Type TIM_MatchConfigStruct;  // Ã¤³Î / ÀÎÅÍ·´Æ® / match½Ã µ¿ÀÛ / output / match value ¼³Á¤ ±¸Á¶Ã¼

void TIMER0_Config(void)
{
   TIM_ConfigStruct.PrescaleOption = TIM_PRESCALE_USVAL;
   TIM_ConfigStruct.PrescaleValue = 100;
   TIM_MatchConfigStruct.MatchChannel = 0;
   TIM_MatchConfigStruct.IntOnMatch = ENABLE;
   TIM_MatchConfigStruct.ResetOnMatch = ENABLE;
   TIM_MatchConfigStruct.StopOnMatch = DISABLE;
   TIM_MatchConfigStruct.ExtMatchOutputType = TIM_EXTMATCH_NOTHING;
   TIM_MatchConfigStruct.MatchValue = 100; 
}

void TIMER0_IRQHandler(void)
{
   TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);
   
}


// -----------------------------------UART---------------------------------------------
void UART0_IRQHandler(void)
{
   
}

// -----------------------------------ADC----------------------------------------------
void ADC_IRQHandler(void)
{
   // ADC 2 Channel È°¼ºÈ  »óÅÂ È®ÀÎ
   if(ADC_ChannelGetStatus(LPC_ADC,ADC_CHANNEL_2,ADC_DATA_DONE))
   {
      ADC_ChannelCmd(LPC_ADC,ADC_CHANNEL_2,DISABLE); // ADC 2 Channel ºñÈ°¼ºÈ  
      adc_value = ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_2); // ADC 2 ChannelÀÇ °ªÀ» ÀÐ¾î¿Í adc_value¿¡ ÀúÀå
      NVIC_DisableIRQ(ADC_IRQn); // Interrupt ºñÈ°¼ºÈ (Interrupt Pending ¿ªÇÒ)
      NVIC_EnableIRQ(ADC_IRQn); // ADC Interrupt È°¼ºÈ  
      ADC_ChannelCmd(LPC_ADC,ADC_CHANNEL_2,ENABLE); // ADC 2 channel È°¼ºÈ 
   }
}


int main(void)
{
   SystemInit();
   
   // --------------------------------LED Init----------------------------------
   Led_Init(LED_ALL);
   
   // --------------------------------FND Init----------------------------------
   FND_Init();
   
   
   // --------------------------------KEYPAD Init-------------------------------
   EXT_IO_init();
   
   
   // --------------------------------SW_INT Init----------------------------------
   EXTI_Init();
   AF_ConfigPin(GPIO_PORT_2, PINSEL_PIN_10, PINSEL_FUNC_1); // Æ÷Æ® 2¹ø 10¹ø ÇÉ -> INT»ç¿ë
   EXTI_ConfigPin(EXTI_EINT0); // 
   NVIC_EnableIRQ(EINT0_IRQn);
   
   // --------------------------------TIMER Init--------------------------------
   TIMER0_Config();
  TIM_Init(LPC_TIM0, TIM_TIMER_MODE, &TIM_ConfigStruct);
  TIM_ConfigMatch(LPC_TIM0, &TIM_MatchConfigStruct);
   NVIC_EnableIRQ(TIMER0_IRQn);
   //TIM_Cmd(LPC_TIM0, ENABLE); // Å¸ÀÌ¸Ó ½ÃÀÛ or Á¤Áö
   
   // --------------------------------UART Init---------------------------------
   Uart0_Init();
   NVIC_EnableIRQ(UART0_IRQn);
   UART_IntConfig(LPC_UART0, UART_INTCFG_RBR, ENABLE);
   
   
   // --------------------------------ADC Init----------------------------------
   AF_ConfigPin(GPIO_PORT_0, PINSEL_PIN_25, PINSEL_FUNC_1);
  ADC_Init(LPC_ADC, 200000); //ADC initialization, ADC Rate -> 200kHz
  ADC_IntConfig(LPC_ADC,ADC_ADINTEN2, ENABLE); // ADC 2Ã¤³Î Interrupt ¼³Á¤
  ADC_ChannelCmd(LPC_ADC, ADC_CHANNEL_2, ENABLE); // ADC 2 channel È°¼ºÈ  
  NVIC_EnableIRQ(ADC_IRQn); // ADC interrupt È°¼ºÈ 
   //ADC_StartCmd(LPC_ADC,ADC_START_NOW); // 1È¸ ADC º¯È¯(°è¼Ó Restart)
   //UARTPutDec16(LPC_UART0,adc_value); // UART0(RS232)·Î adc_value °ª Ãâ·Â
   
}
