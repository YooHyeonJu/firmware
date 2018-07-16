#include "lcd.h"
#include <stdio.h>


int main()
{
	int x,y;
	/*
	int r = RED;
	int g = GREEN;
	int b = BLUE;
	int k = BLACK;
	*/
	
 short sample16bpp = 0xF800;

 int r = (int)( ( sample16bpp >> ( 5 + 6 ) ) & 31 );

 int g = (int)( ( sample16bpp >> 5 ) & 63 );

 int b = (int)( sample16bpp & 31 );

 int R = r * 255 / 31;

 int G = g * 255 / 63;

 int B = b * 255 / 31;

 int convertedRGB = ( R << 16 ) | ( G << 8 ) | B;
	
	LCD_Init();  // LCD init
	
	LCD_clear();	//LCD clear
	for(x = 0;x<WIDTH/2;x++)
	{
		for(y = 0;y<HEIGHT/2;y++)
		{
				LCD_PutPixel(x,y,RED);
		}
	}
	for(x = 0;x<WIDTH/2;x++)
	{
		for(y = HEIGHT/2;y<HEIGHT;y++)
		{
			LCD_PutPixel(x,y,GREEN);
		}
	}
	for(x = WIDTH/2;x<WIDTH;x++)
	{
		for(y = 0;y<HEIGHT/2;y++)
		{
			LCD_PutPixel(x,y,BLUE);
		}
	}
	for(x = WIDTH/2;x<WIDTH;x++)
	{
		for(y = HEIGHT/2;y<HEIGHT;y++)
		{
			LCD_PutPixel(x,y,convertedRGB);
		}
	}
	
	
	/*
	for(x = 0;x<WIDTH;x++)
	{
		for(y = 0;y<HEIGHT;y++)
		{
			if(x%3 == 0)
			{
				LCD_PutPixel(x,y,r);
			}
			if(x%3 == 1)
			{
				LCD_PutPixel(x,y,g);
			}
			if(x%3 == 2)
			{
				LCD_PutPixel(x,y,b);
			}
		}
	}
	*/
	
	
}