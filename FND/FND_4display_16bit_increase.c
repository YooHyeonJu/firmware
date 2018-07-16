#include "LPC1768_fnd.h"
#include "LPC1768_utility.h"

int main()
{
	FND_Init();
	int i = 0;
	int j = 0;
	
	while(1)
	{
		
			FND_COM_DATA_Select(8,j%16);
			Delay(5000);
			FND_COM_DATA_Select(7,(j/16)%16);
			Delay(5000);
			FND_COM_DATA_Select(6,(j/(16*16))%16);
			Delay(5000);
			FND_COM_DATA_Select(5,(j/(16*16*16))%16);
			Delay(5000);
			
			if(++i%100 == 0)
			{
				j++;
			}
		
	}
}