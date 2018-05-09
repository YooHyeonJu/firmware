#include "LPC17xx.H"
#include "LPC1768_utility.h"
#include "LPC1768_fnd.h"
#include "Keypad.H"

uint8_t num = 0;

void clear()
{
	LPC_GPIO0->FIOPIN &= ~(1<<4);
	LPC_GPIO0->FIODIR &= ~(1<<23);
	LPC_GPIO0->FIODIR &= ~(1<<24);
	LPC_GPIO3->FIODIR &= ~(1<<25);
	LPC_GPIO3->FIODIR &= ~(1<<26);
	LPC_GPIO0->FIOPIN &= ~(1<<5);
	LPC_GPIO0->FIOPIN &= ~(1<<10);
	LPC_GPIO2->FIOPIN &= ~(1<<12);
	LPC_GPIO2->FIOPIN &= ~(1<<13);
}

void Increase()
{
	num++;
	Delay(3000);
}

void Keypad_test()
{
	uint8_t Keypad_Value = 0;
	Keypad_DIR_Input();
	Keypad_Value = Keypad('C');
	Delay(5000);
	clear();
	EXT_IO_B_CS();
	FND_Init();
	if(Keypad_Value == 3)
	{
		Increase();
	}
	FND_COM_DATA_Select(8,num%16);
	Delay(5000);
	//FND_COM_DATA_Select(7,num/16);
}

int main(void)
{
	SystemInit();
	Led_Init(LED_ALL);
	EXT_IO_init();
	
	for(;;)
	{
		Keypad_test();
	}
}