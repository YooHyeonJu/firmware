#include "LPC1768_utility.h"


/////////POLLING ���
int main(void)
{
	uint32_t Button_Status = 0;
	Led_Init(LED_ALL);	//LED��ü �ʱ�ȭ
	GPIO_SetDir(GPIO_PORT_2,(1<<10),INPUT);
	//Set 10 of GPIO2 as input -> INT Button input
	
	while(1)
	{
		//���������� ��ư�� ���¸� Read�Ͽ� ���°��� Button_Status�� �����ϰ� �Ǻ��Ѵ�.
		Button_Status = (GPIO_ReadValue(GPIO_PORT_2)&(1<<10));
		//GPIO_ReadValue �� �ش� PORT�� 32Bit���� ��ȯ�Ѵ�.
		
		if(Button_Status == 0)	//INT Button�� ������ ��
		{
			Led_All_On();//��� LED�� �Ҵ�.
		}
		else	//INT Button������ �ʾ��� ��
		{
			Led_All_Off();	//��� LED�� ����.
		}
	}
}