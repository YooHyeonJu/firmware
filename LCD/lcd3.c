#include "lcd.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PI 3.14

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

void rotate_circle(int x,int y,int r,double theta, int white)
{
	int i,j;
	for( i = -200;i<WIDTH;i++)
	{
		for(j = -200;j<HEIGHT;j++)
		{
						
			if(((r-1)*(r-1) <= i*i+ j*j) && ((r*r) > i*i+j*j))
			{
				int x_ = i*cos((PI*theta)/180)+j*sin((PI*theta)/180);
				int y_ = -i*sin((PI*theta)/180)+j*cos((PI*theta)/180);
				
				if(white == 1)
					LCD_PutPixel(x_+x,y+y_,0x001F);
				else
					LCD_PutPixel(x_+x,y+y_,0xFFFF);
			}
		}
	}
}

int main()
{
	LCD_Init();
	LCD_clear();
	
	int a,b,c,size;

	//srand(time(NULL));
	
	
	
	/*
	for(double i = 0.0;i<360;i+=10)
	{
		rotate_circle(100+i*0.1,100,20,i,1);
		if(i!=0)
			rotate_circle(100+(i-10)*0.1,100,20,(i-10),0);
	}
	*/
	
		draw_circle(10,10,10,10);
	
	for(int i = 0; i <100;i++)
	{
		int a = rand()%320;
		int b = rand()%240;
		int c = rand()%65535;
		int size = rand()%10;
		//draw_circle(100+i,100+i,10);
		draw_circle(a,b,size,c);
	}
}