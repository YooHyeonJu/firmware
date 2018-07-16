#include "lcd_header.h"

int main()
{
	int x,y;
	
	int r = Red;
	int g = Green;
	int b = Blue;
	int k = Black;

	
	GLCD_init();  // LCD init
	GLCD_clear(White);	//LCD clear
	
	for(x = 0;x<WIDTH/2;x++)
	{
		for(y = 0;y<HEIGHT/2;y++)
		{
				LCD_PutPixel(x,y,r);
		}
	}
	for(x = 0;x<WIDTH/2;x++)
	{
		for(y = HEIGHT/2;y<HEIGHT;y++)
		{
			LCD_PutPixel(x,y,g);
		}
	}
	for(x = WIDTH/2;x<WIDTH;x++)
	{
		for(y = 0;y<HEIGHT/2;y++)
		{
			LCD_PutPixel(x,y,b);
		}
	}
	for(x = WIDTH/2;x<WIDTH;x++)
	{
		for(y = HEIGHT/2;y<HEIGHT;y++)
		{
			LCD_PutPixel(x,y,k);
		}
	}	
}