#define WIDTH  320   // lcd ����
#define HEIGHT 240   // lcd ����

#define BPP    16    // 16bit RGB
#define RED		  0xF800
#define GREEN 	0x07E0
#define BLUE 		0x001F
#define BLACK		0x0000

#define PINSEL0		(*(volatile int *)0x4002C000)
#define PINSEL9		(*(volatile int *)0x4002C024)
#define FIO0DIR 	(*(volatile int *)0x2009C000)
#define FIO4DIR		(*(volatile int *)0x2009C080)
#define FIO0PIN		(*(volatile int *)0x2009C014)
#define FIO4PIN		(*(volatile int *)0x2009C094)
#define PCLKSEL0 	(*(volatile int *)0x400FC1A8)
#define PCONP	 		(*(volatile int *)0x400FC0C4)

#define SSP1CR0	 	(*(volatile int *)0x40030000)
#define SSP1CR1	 	(*(volatile int *)0x40030004)
#define SSP1CPSR	(*(volatile int *)0x40030010)
#define SSP1SR		(*(volatile int *)0x4003000C)
#define SSP1DR 		(*(volatile int *)0x40030008)

#define CMD 0x000
#define DAT 0x100



void _delay(double s)
{
	int i;
	int time = s*12000000;
	for(i = 0;i<time;i++);
}


void LCD_Init()
{
	/* ----- lcd control pin ------ */
	PINSEL9 &= ~(3<<24); // P4.28 lcd backlight
	PINSEL9 &= ~(3<<26); // P4.29 lcd CS
	
	FIO4DIR |=  (1<<28);	//output
	FIO4DIR |=  (1<<29);	//output
	FIO4PIN |=  (1<<29);	//pin -> high
	
	/* ----- SPI pin ------ */
	//PCLKSEL0 |= (2<<16); 
	PCLKSEL0 |= (1<<17); 
	PCONP |= (1<<10);			//Enable power to SPI block
	FIO0DIR |= (1<<6); 		// P0.6 GPIO output SSEL1
	PINSEL0 |= (1<<15)|(1<<17)|(1<<19);
	SSP1CR0 = (0<<7) | // CPHA = 0
	          (0<<6) | // CPOL = 0
			  (0<<4) | // Frame format = SPOI
			  (8<<0); //  data 9-bits	
	SSP1CPSR = 2;  // ��� �ӵ� ���� ���� ���������� ��������.
	SSP1CR1 = (1<<1);  // Enable SSP1  

	SSP1DR = (CMD | (0x3A)); // pixel Format ,134p
	SSP1DR = (DAT | (0x55)); // 16bits / pixel
	
	SSP1DR = (CMD | (0x36)); // ���÷��� ���� ���� , 127p (MY , MX, MV, ML, BGR ,MH)
	SSP1DR = (DAT | (0xB8)); // BGR bit�� 1�� �־�� RGB�� �۵�
	 
	SSP1DR = (CMD | (0xB6)); // Display Function Control (B6h) , 165p
	SSP1DR = (DAT | (0x0A)); //  1 parameter
	SSP1DR = (DAT | (0xA2)); //  2 parameter
	SSP1DR = (DAT | (0x27)); //  3 parameter
	
	SSP1DR = (CMD | (0x11)); //  sleep
	_delay(0.12);            //  sleep for delay 120ms 
	
	SSP1DR = (CMD | (0x29)); // memory -> display panel
	
	FIO4PIN |= (1<<28); // backlight control enable
}

/* CS : Chip Select
 * SR : Status register
 * DCX = '0' , command select
 *     = '1' , data select  */

void wr_cmd(unsigned char c)
{
	FIO0PIN &= ~(1<<6); // CS pin enable
	SSP1DR = (CMD | c); // ������ ������~~~~~~
	while(SSP1SR & (1<<4)); // �����Ͱ� ���۵� �� ���� ��ٷ�����
	FIO0PIN |= (1<<6);	// CS pin disable
}

void wr_dat(unsigned char c)
{
	FIO0PIN &= ~(1<<6);
	SSP1DR = (DAT | c);
	while(SSP1SR & (1<<4));
	FIO0PIN |= (1<<6);
}

// 0x2C : ������ ����
// ������ ������ �ȼ� �ϳ��� �����Ϳ� �ִ´� 
// 16bit �� ���߾� �ش�. (16 bit RGB)
void wr_pixel(unsigned short c)
{
	FIO0PIN &= ~(1<<6);
	SSP1DR = (DAT | (c>>8)); // low 8bit
	while(SSP1SR & (1<<4)); // ������ ���� ���
	SSP1DR = (DAT | c); // high 8bit
	while(SSP1SR & (1<<4)); // ������ ���� ���
	FIO0PIN |= (1<<6);
}
 
// Column Address Set
void LCD_SetX(unsigned int x, unsigned int width)
{
	wr_cmd(0x2A);
	wr_dat((x>>8));
	wr_dat(x);
	wr_dat(((x+width-1)>>8));
	wr_dat((x+width-1));
}

// Page Address Set 
void LCD_SetY(unsigned int y, unsigned int height)
{
	wr_cmd(0x2B);
	wr_dat((y>>8));
	wr_dat(y);
	wr_dat(((y+height-1)>>8));
	wr_dat((y+height-1));
}

void LCD_PutPixel(unsigned int x, unsigned int y, unsigned short color)
{
	LCD_SetX(x,1);
	LCD_SetY(y,1);
	
	wr_cmd(0x2C); // ������ġ ����
	wr_pixel(color);
}

/*  Memory Write : MCU -> frame memory �� ���۵�
 *  (0x2C)        ����� ���εǸ� ��/���� ������ ��ġ�� �缳��.*/

void LCD_clear()
{
	int i;
	/* ����, ���� ������ ������ �ʱ�ȭ */
	LCD_SetX(0, WIDTH); // x�� 0~320 ���� �ʱ�ȭ
	LCD_SetY(0, HEIGHT); // y�� 0~ 240 ���� �ʱ�ȭ
	
	wr_cmd(0x2C); // Memory Write
	
	for(i = 0;i<WIDTH*HEIGHT;i++)
		wr_pixel(0xFFFF); // ���(FFFF)�� ȭ�� �ʱ�ȭ
}