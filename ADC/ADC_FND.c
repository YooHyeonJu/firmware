#include "lpc17xx_adc.h"
#include "LPC1768_utility.h"
#include "debug_frmwrk.h"
#include "LPC1768_fnd.h"


uint16_t adc_value;
void ADC_IRQHandler(void);
void LED_Binary(uint16_t _value);


int main(void)
{
	
	uint8_t menul[] = "*********************************************************\n\r"
	"\t UART0 Init / ADC Interrupt Example\r\n"
	"\t - MCU: LPC1768 \r\n"
	"\t - Communicate via: UART0 - 115200bps \r\n"
	"*********************************************************\n\r";
	
	 Led_Init(LED_ALL);

	
	FND_Init();
	//Uart0_Init();
	int i = 0;
	//UARTPuts(LPC_UART0,menul);
	
	int low = 0;
	int high = 0;
	
	AF_ConfigPin(GPIO_PORT_0, PINSEL_PIN_25, PINSEL_FUNC_1);
	
	ADC_Init(LPC_ADC,200000);
	ADC_IntConfig(LPC_ADC,ADC_ADINTEN2,ENABLE);
	ADC_ChannelCmd(LPC_ADC,ADC_CHANNEL_2,ENABLE);
	NVIC_EnableIRQ(ADC_IRQn);
	
	while(1)
	{
		
		
		if(++i%500 == 0)
		{
			ADC_StartCmd(LPC_ADC,ADC_START_NOW);
		}
		
		
		FND_COM_DATA_Select(8,adc_value%16);
		Delay(5000);
		FND_COM_DATA_Select(7,(adc_value/16)%16);
		Delay(5000);
		FND_COM_DATA_Select(6,(adc_value/(16*16))%16);
		Delay(5000);
		FND_COM_DATA_Select(5,(adc_value/(16*16*16))%16);
		Delay(5000);
		
		//low = adc_value%16;
		//high = (adc_value/16)%16;
		
		
		LED_Binary(adc_value);
		
		//UARTPuts(LPC_UART0,"ADC value on channel 2: ");
		//UARTPutDec16(LPC_UART0,adc_value);
		//UARTPuts(LPC_UART0,"\r\n");
		
		
	}
	
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

void LED_Binary(uint16_t _value){
   Led_All_Off();
   if(_value & (0x01<<7)){
      Led_On(1);
   }
   if(_value & (0x01<<6)){
      Led_On(2);
   }
   if(_value & (0x01<<5)){
      Led_On(3);
   }
   if(_value & (0x01<<4)){
      Led_On(4);
   }
   if(_value & (0x01<<3)){
      Led_On(5);
   }
   if(_value & (0x01<<2)){
      Led_On(6);
   }
   if(_value & (0x01<<1)){
      Led_On(7);
   }
   if(_value & (0x01)){
      Led_On(8);
   }
}
