#include "lcd_header.h"

int main()
{
	GLCD_init();
	GLCD_clear(Black);

	int a,b,c;
	int i,j;
	
	unsigned short background[320][240] = {0};

	for(i = 0; i <100;i++)
	{
		a = rand()%320;
		b = rand()%240;
		c = rand()%65535;
		
		LCD_PutPixel(a,b,c);
		LCD_PutPixel(a+1,b+1,c);
		LCD_PutPixel(a,b+1,c);
		LCD_PutPixel(a+1,b,c);
		
	}
	
	
	for(i = 0;i<WIDTH;i++)
	{
		for(j = 0 ;j<HEIGHT;j++)
		{
			background[i][j] = 
		}
	}
	
	

}