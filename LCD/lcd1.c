#include "lcd.h"

int main()
{
	int x,y;
	
	int r = RED;
	int g = GREEN;
	int b = BLUE;
	
	LCD_Init();  // LCD 초기화
	
	LCD_clear();
	for(x = 0;x<WIDTH/2;x++)
	{
		int gtemp = g;
		for(y = 0;y<HEIGHT/2;y++)
		{
			if(y !=0 && y % 2 == 0)
				gtemp = gtemp - 0x0020;
			
			LCD_PutPixel(x,y,r+gtemp);
			LCD_PutPixel(WIDTH-x-1,y,b+gtemp);
			
			LCD_PutPixel(x,HEIGHT-y-1,r+gtemp);
			LCD_PutPixel(WIDTH-x-1,HEIGHT-y-1,b+gtemp);
			
		}
		if(x != 0&&  x % 5 == 0)
		{
			r = r - 0x0800;
			b = b -1;
		}
	}
}
