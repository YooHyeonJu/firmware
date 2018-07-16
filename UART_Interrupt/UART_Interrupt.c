#include "LPC1768_utility.h"
#include "debug_frmwrk.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int main(void)
{
	Led_Init(LED_ALL);
	Uart0_Init();
	NVIC_EnableIRQ(UART0_IRQn);
	UART_IntConfig(LPC_UART0,UART_INTCFG_RBR,ENABLE);
	
	while(1)
	{
		
	}
}

void UART0_IRQHandler(void)
{
	uint8_t ch = 0;
	ch = UART_ReceiveByte(LPC_UART0);
	UART_SendByte(LPC_UART0,ch);
}