#include<lpc21xx.h>

#define LCD 0xff
#define R 1<<8
#define E 1<<9

void lcd_inst(void);
void lcd_cmd(unsigned char cmd);
void lcd_data(unsigned char data);

void delay_ms()
{
	  T0PR =  15000-1;
	  T0TCR = 0x01;
	  
	  while(T0TC<2);

	  T0TCR = 0x03;
	  T0TCR = 0x00; 
}

void lcd_inst(void)
{
 	IODIR0 = LCD | R | E;
	lcd_cmd(0x01);
	lcd_cmd(0x02);
	lcd_cmd(0x0c);
	lcd_cmd(0x38);
	lcd_cmd(0x80);
}

void lcd_cmd(unsigned char cmd)
{
	IOCLR0 = LCD;
	IOSET0 = cmd;
	IOCLR0 = R;
	IOSET0 = E;
	delay_ms();
	IOCLR0 = E;
}

void lcd_data(unsigned char data)
{
   	IOCLR0 = LCD;
	IOSET0 = data;
	IOSET0 = R;
	IOSET0 = E;
	delay_ms();
	IOCLR0 = E;
}
