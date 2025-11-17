#include<lpc21xx.h>
#define data_pins 0xFF
#define rs 1<<21
#define e 1<<22
void delay(int ms)
{
	T0PR=15000-1;
	T0TCR=0X00;
	T0TCR=0x01;
	while(T0TC<ms);
	T0TCR=0x03;
	T0TCR=0X01;
}
void lcd_init(void);
void cmd(unsigned char);
void data(unsigned char);
void string(char*);
void lcd_init(void)
{
	IODIR0 |= data_pins |rs |e;
	cmd(0x01);
	cmd(0x02);
	cmd(0x0c);
	cmd(0x38);
	cmd(0x80);
}
void cmd(unsigned char cmd)
{
	IOCLR0 =data_pins;
	IOSET0 =cmd;
	IOCLR0 =rs;
	IOSET0 =e;
	delay(2);
	IOCLR0= e;
}

void data(unsigned char datas)
{
	IOCLR0 =data_pins;
	IOSET0 =datas;
	IOSET0 =rs;
	IOSET0 =e;
	delay(2);
	IOCLR0= e;
}

void string(char*s)
{
	
	while(*s)
	{
		data(*s++);
	}
}
