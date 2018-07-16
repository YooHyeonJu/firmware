#include "LPC1768_fnd.h"
#include "LPC1768_utility.h"

int main()
{
	FND_Init();
	
	while(1)
	{
		for(int i = 0;i<10;i++)
		{
			FND_COM_Init();//포트 값 초기화
			GPIO_SetValue(GPIO_PORT_3,(1<<26)); //DIC 8
			GPIO_SetValue(GPIO_PORT_3,(1<<25)); //DIC 7
			GPIO_SetValue(GPIO_PORT_2,(1<<12)); //DIC 6
			GPIO_SetValue(GPIO_PORT_2,(1<<13)); //DIC 5
			FND_COM_CS(); 	// FND_COM_CS세팅
			
			FND_DATA_Select(i%10);	//각 자리 디스플레이에 출력
			Delay(SEC_1);	//1초 딜레이
		}
	}
}