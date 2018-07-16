#include "lcd.h"

unsigned long myfont[32]
= { 0x00000000,0x00000000,0x00FFC000,0x01F04000,0x00004000,0x00004000,0x00004000,
0x00004000,0x03FFE000,0x00800000,0x00800000,0x00FFF000,0x00F00000,0x00000F00,
0x001FF000,0x03f80000,0x0e000000,0x001ff000,0x00f81000,0x00001000,0x00011c00,
0x007fe000,0x01c00000,0x00600000,0x00600000,0x00600000,0x00600000,0x007ffe00,
0x00600000,0x00000000,0x00000000,0x00000000
	};
void font_line(int x,int y) // 폰트 그리기
{
	int i,j;
	for(i = 0; i<32;i++)
	{
		  for( j = 0; j<32;j++)
		  {
			 if (myfont[i] & (0x80000000>>j)) 
			 {
				LCD_PutPixel(x+j,y+i,0);
			 }
		 }
   }
}

int main()
{
	int x,y, k = 0;
	int temp = 16;
	LCD_Init();  // LCD 초기화
	LCD_clear();
	font_line(100,100);
}
