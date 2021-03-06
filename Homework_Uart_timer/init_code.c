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

char rcv_buff[100] = {0}; // 입력한 값을 받을 버퍼
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

void TIMER0_Config(void); // timer 설정

TIM_TIMERCFG_Type TIM_ConfigStruct;            // 프리스케일 옵션 및 값
TIM_MATCHCFG_Type TIM_MatchConfigStruct;  // 채널 / 인터럽트 / match시 동작 / output / match value 설정 구조체

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
   // ADC 2 Channel 활성�  상태 확인
   if(ADC_ChannelGetStatus(LPC_ADC,ADC_CHANNEL_2,ADC_DATA_DONE))
   {
      ADC_ChannelCmd(LPC_ADC,ADC_CHANNEL_2,DISABLE); // ADC 2 Channel 비활성�  
      adc_value = ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_2); // ADC 2 Channel의 값을 읽어와 adc_value에 저장
      NVIC_DisableIRQ(ADC_IRQn); // Interrupt 비활성� (Interrupt Pending 역할)
      NVIC_EnableIRQ(ADC_IRQn); // ADC Interrupt 활성�  
      ADC_ChannelCmd(LPC_ADC,ADC_CHANNEL_2,ENABLE); // ADC 2 channel 활성� 
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
   AF_ConfigPin(GPIO_PORT_2, PINSEL_PIN_10, PINSEL_FUNC_1); // 포트 2번 10번 핀 -> INT사용
   EXTI_ConfigPin(EXTI_EINT0); // 
   NVIC_EnableIRQ(EINT0_IRQn);
   
   // --------------------------------TIMER Init--------------------------------
   TIMER0_Config();
  TIM_Init(LPC_TIM0, TIM_TIMER_MODE, &TIM_ConfigStruct);
  TIM_ConfigMatch(LPC_TIM0, &TIM_MatchConfigStruct);
   NVIC_EnableIRQ(TIMER0_IRQn);
   //TIM_Cmd(LPC_TIM0, ENABLE); // 타이머 시작 or 정지
   
   // --------------------------------UART Init---------------------------------
   Uart0_Init();
   NVIC_EnableIRQ(UART0_IRQn);
   UART_IntConfig(LPC_UART0, UART_INTCFG_RBR, ENABLE);
   
   
   // --------------------------------ADC Init----------------------------------
   AF_ConfigPin(GPIO_PORT_0, PINSEL_PIN_25, PINSEL_FUNC_1);
  ADC_Init(LPC_ADC, 200000); //ADC initialization, ADC Rate -> 200kHz
  ADC_IntConfig(LPC_ADC,ADC_ADINTEN2, ENABLE); // ADC 2채널 Interrupt 설정
  ADC_ChannelCmd(LPC_ADC, ADC_CHANNEL_2, ENABLE); // ADC 2 channel 활성�  
  NVIC_EnableIRQ(ADC_IRQn); // ADC interrupt 활성� 
   //ADC_StartCmd(LPC_ADC,ADC_START_NOW); // 1회 ADC 변환(계속 Restart)
   //UARTPutDec16(LPC_UART0,adc_value); // UART0(RS232)로 adc_value 값 출력
   
}
