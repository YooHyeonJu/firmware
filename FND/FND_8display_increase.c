#include "LPC1768_fnd.h"
#include "LPC1768_utility.h"

int main()
{
	FND_Init();
	int i = 0;
	int j = 0;

	
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
		
			//j++;
			
			if(++i%100 == 0)
			{
				j++;
			}
			
			
	}
}