#include "LPC1768_utility.h"


/////////POLLING 방식
int main(void)
{
	uint32_t Button_Status = 0;
	Led_Init(LED_ALL);	//LED전체 초기화
	GPIO_SetDir(GPIO_PORT_2,(1<<10),INPUT);
	//Set 10 of GPIO2 as input -> INT Button input
	
	while(1)
	{
		//지속적으로 버튼의 상태를 Read하여 상태값을 Button_Status에 저장하고 판별한다.
		Button_Status = (GPIO_ReadValue(GPIO_PORT_2)&(1<<10));
		//GPIO_ReadValue 는 해당 PORT의 32Bit값을 반환한다.
		
		if(Button_Status == 0)	//INT Button을 눌렀을 때
		{
			Led_All_On();//모든 LED를 켠다.
		}
		else	//INT Button눌리지 않았응 때
		{
			Led_All_Off();	//모든 LED를 끈다.
		}
	}
}