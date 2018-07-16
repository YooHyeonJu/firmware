#include "lcd_header.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PI 3.14

void draw_triangle(int x,int y,int r,int color)
{
	int i,j;
	int a,b;
	for( i = 0;i<WIDTH;i++)
	{
		for(j = 0;j<HEIGHT;j++)
		{
			if((x == i) && (y == j))
			{
				for(a = 0;a<r;a++)
				{
					for(b = 0;b<r;b++)
					{
						if(a<=b)
							LCD_PutPixel(i+a,j+b,color);	
					}
				}
			}
		}
	}
}

void draw_square(int sx, int sy,int l, int color)
{
	int i,j;
	int ex = sx + l;
	int ey = sy + l;
	for( i = 0;i<WIDTH;i++)
	{
		for(j = 0;j<HEIGHT;j++)
		{
			if((sx<i && i<ex) && (sy<j && j<ey))
					LCD_PutPixel(i,j,color);
		}
	}
}


void draw_circle(int x,int y,int r,int color)
{
	int i,j;
	for( i = 0;i<WIDTH;i++)
	{
		for(j = 0;j<HEIGHT;j++)
		{
			int v = i-x;
			int w = j-y;
			if(((r-2)*(r-2) <= v*v+ w*w) && ((r*r) > v*v+w*w))
					LCD_PutPixel(i,j,color);
		}
	}
}





int main()
{
	GLCD_init();
	GLCD_clear(White);
	
	GLCD_setBackColor(Red);
	int a,b,c,size;

	for(int i = 0; i <100;i++)
	{
		a = rand()%320;
		b = rand()%240;
		c = rand()%65535;
		size = rand()%25;
	
		draw_triangle(a,b,size,c);
		//draw_square(a,b,size,c);
		//draw_circle(a,b,size,c);
		
		GLCD_setBackColor(Green);
	}
	
	
	GLCD_setBackColor(Blue);
	//void GLCD_setBackColor(unsigned short color)

}