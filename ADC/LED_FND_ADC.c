#include "LPC1768_utility.h"
#include "LPC1768_fnd.h"
#include "lpc17xx_adc.h"

uint16_t adc_value;

int main(void)
{
   int i=0;
   // LED
   Led_Init(LED_ALL);
   // ADC
   AF_ConfigPin(GPIO_PORT_0,PINSEL_PIN_25,PINSEL_FUNC_1);
   ADC_Init(LPC_ADC,200000);
   ADC_IntConfig(LPC_ADC,ADC_ADINTEN2,ENABLE);
   ADC_ChannelCmd(LPC_ADC,ADC_CHANNEL_2,ENABLE);
   NVIC_EnableIRQ(ADC_IRQn);
   // FND
   FND_Init();
   AF_ConfigPin(GPIO_PORT_2,PINSEL_PIN_10,PINSEL_FUNC_1);
   ADC_StartCmd(LPC_ADC,ADC_START_NOW);
   while(1){
      if(++i%500==0){
         ADC_StartCmd(LPC_ADC,ADC_START_NOW);
      }
      FND_COM_DATA_Select(8,(uint8_t)(adc_value%16));
      Delay(5000);
      FND_COM_DATA_Select(7,((uint8_t)(adc_value/16)%16));
      Delay(5000);
      FND_COM_DATA_Select(6,((uint8_t)(adc_value/(16*16))%16));
      Delay(5000);
      FND_COM_DATA_Select(5,((uint8_t)(adc_value/(16*16*16))%16));
      Delay(5000);
      
   }
}


void ADC_IRQHandler(void){
   if(ADC_ChannelGetStatus(LPC_ADC,ADC_CHANNEL_2,ADC_DATA_DONE)){
      ADC_ChannelCmd(LPC_ADC,ADC_CHANNEL_2,DISABLE);
      adc_value=ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_2);
      NVIC_DisableIRQ(ADC_IRQn);
      NVIC_EnableIRQ(ADC_IRQn);
      ADC_ChannelCmd(LPC_ADC,ADC_CHANNEL_2,ENABLE);
   }
}