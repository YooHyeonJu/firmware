#include "LPC1768_utility.h"

int main()
{
	Led_Init(LED_ALL);//LED ��ü �ʱ�ȭ
	
	while(1)
	{
		Led_All_On();
		Delay(SEC_1);//Delay 1sec
		Led_All_Off();
		Delay(SEC_1);
	}
	
}