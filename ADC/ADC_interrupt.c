#include "lpc17xx_adc.h"
#include "LPC1768_utility.h"
#include "debug_frmwrk.h"

uint16_t adc_value;
void ADC_IRQHandler(void);

int main(void)
{
	uint8_t menul[] = "*********************************************************\n\r"
	"\t UART0 Init / ADC Interrupt Example\r\n"
	"\t - MCU: LPC1768 \r\n"
	"\t - Communicate via: UART0 - 115200bps \r\n"
	"*********************************************************\n\r";
	
	
	Uart0_Init();
	
	UARTPuts(LPC_UART0,menul);
	
	AF_ConfigPin(GPIO_PORT_0, PINSEL_PIN_25, PINSEL_FUNC_1);
	
	ADC_Init(LPC_ADC,200000);
	ADC_IntConfig(LPC_ADC,ADC_ADINTEN2,ENABLE);
	ADC_ChannelCmd(LPC_ADC,ADC_CHANNEL_2,ENABLE);
	NVIC_EnableIRQ(ADC_IRQn);
	
	while(1)
	{
		ADC_StartCmd(LPC_ADC,ADC_START_NOW);
		UARTPuts(LPC_UART0,"ADC value on channel 2: ");
		UARTPutDec16(LPC_UART0,adc_value);
		UARTPuts(LPC_UART0,"\r\n");
		Delay(SEC_1);
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
