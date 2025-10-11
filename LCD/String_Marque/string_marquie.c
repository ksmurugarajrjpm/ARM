#include<lpc21xx.h>
#include "lcd_header.h"
			  
void lcd_str(char*);

	char a = 0x80;

int main()
{

 	lcd_inst();

	while(1){

	lcd_str("Embedded System  ");
	lcd_cmd(a++);

	if(a==0x91)
		a = 0x80;
	lcd_cmd(0x01);
	}	
}

void lcd_str(char *str)
{	
    int b = a;

 	while(*str){
		lcd_cmd(b++);
		lcd_data(*str++);

		if(b==0x91)
		b = 0x80;
	}
	delay_ms(500);
}
