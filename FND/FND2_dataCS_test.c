#include "LPC1768_fnd.h"
#include "LPC1768_utility.h"

int main()
{
	FND_Init();
	int i = 0;
	int j = 0;
	
	//FND_COM_DATA_Select(1,1);
	//FND_COM_DATA_Select(2,9);
	while(1){
	/* 1, 1*/
	FND_COM_Init();
	GPIO_SetValue(GPIO_PORT_0,(1<<23));
	//FND_COM_CS();	
	LPC_GPIO0->FIOPIN |= (1<<10);
	LPC_GPIO0->FIOPIN &= ~(1<<10);
	
	FND_Data_Reset();
	GPIO_ClearValue(GPIO_PORT_0,FND_B);
	GPIO_ClearValue(GPIO_PORT_1,FND_C);
	//FND_Data_CS();
	GPIO_SetValue(GPIO_PORT_0,(1<<5));		
	GPIO_ClearValue(GPIO_PORT_0,(1<<5));
	
	Delay(400000);
	
	/*2, 9 */
	FND_COM_Init();
	GPIO_SetValue(GPIO_PORT_0,(1<<24));	//	DIC 2
	//FND_COM_CS();	
	LPC_GPIO0->FIOPIN |= (1<<10);
	LPC_GPIO0->FIOPIN &= ~(1<<10);
	
	
	FND_Data_Reset();
	GPIO_ClearValue(GPIO_PORT_0,FND_A | FND_B);
	GPIO_ClearValue(GPIO_PORT_1,FND_C);
	GPIO_ClearValue(GPIO_PORT_2,FND_F);	
	GPIO_ClearValue(GPIO_PORT_3,FND_G);
	//FND_Data_CS();
	GPIO_SetValue(GPIO_PORT_0,(1<<5));		
	GPIO_ClearValue(GPIO_PORT_0,(1<<5));
	
	
	Delay(400000);
}
	
	return 0;
	
	
	/*
	FND_Data_Reset();
	for(j=1234;j<9244;j++){
	
		  FND_COM_DATA_Select(1,(j/(10*10*10))%10);
		FND_COM_DATA_Select(2,(j/(10*10))%10);
		FND_COM_DATA_Select(3,(j/10)%10);
		  FND_COM_DATA_Select(4,j%10);
			
			
			
      Delay(100000);
	}
	return 0;
	*/
	
	
	while(1)
	{
		
			FND_COM_DATA_Select(8,j%10);
			Delay(500000);
			FND_COM_DATA_Select(7,(j/10)%10);
			Delay(500000);
			FND_COM_DATA_Select(6,(j/(10*10))%10);
			Delay(500000);
			FND_COM_DATA_Select(5,(j/(10*10*10))%10);
			Delay(500000);
			FND_COM_DATA_Select(4,(j/(10*10*10*10))%10);
			Delay(500000);
			FND_COM_DATA_Select(3,(j/(10*10*10*10*10))%10);
			Delay(500000);
			FND_COM_DATA_Select(2,(j/(10*10*10*10*10*10))%10);
			Delay(500000);
			FND_COM_DATA_Select(1,(j/(10*10*10*10*10*10*10))%10);
			Delay(500000);
		
			j++;
			/*
			if(++i%100 == 0)
			{
				j++;
			}
			*/
			
	}
}