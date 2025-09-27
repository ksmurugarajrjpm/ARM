#include<lpc21xx.h>

#define LCD 0xff
#define R 1<<8
#define E 1<<9

void lcd_inst(void);
void delay_ms(void);
void lcd_cmd(unsigned char);
void lcd_data(unsigned char);

void delay_ms(void)
{
	 T0PR = 15000-1;
	 T0TCR = 0X01;
	 while(T0TC<2);
	 		T0TCR = 0X03;
		   T0TCR = 0X00;

}

void lcd_inst(void)
{
 	IODIR0 = LCD | R | E;
	lcd_cmd(0x01);
	lcd_cmd(0x02);
	lcd_cmd(0x0c);
	lcd_cmd(0x38);
	//lcd_cmd(0x80);
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
