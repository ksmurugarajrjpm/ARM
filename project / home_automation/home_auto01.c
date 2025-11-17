#include<lpc21xx.h>
#include<string.h>
#include"4_bit.h"

#define LED_1 1<<15 

void UART_CONFIG(void);

int i=0,k,n=1,c,r=1,z;
char dat;
char arr[100],arr1[9];;
void inter(void) __irq
{
	dat=U1RBR;
	if((dat >='a')&&(dat <='z'))
	{
		dat=dat^32;
	}
	if(dat == '\r' || dat == '\n')
	{
    	arr[i] = '\0';
    	i = 0;
	c=7;
	}
	else
	{
    	arr[i++] = dat;
	}
	if(c==7)
	{

		cmd(0xc0);
		string(arr);
		c=0;
	} 
		

	VICVectAddr=0;
	
}
int main()
{
	lcd_init();
	UART_CONFIG();
	cmd(0x80);
	string("HOME AUTOMATION");
	VICIntSelect=0;
	VICVectCntl0=(0x20)|7;
	VICVectAddr0=(unsigned long)inter;
	U1IER=0X03;
	VICIntEnable=1<<7;
	while(1)
	{
	n=strncmp(arr,"FAN OFF",7);
	k=strncmp(arr,"FAN ON",6);
	 if((n==0)&&(r==0)||((z%2)==0))
		{
			
		   IOSET0=1<<17;
		   IOSET0=1<<18;
		   
	
		}
	if((k==0)||(((IOPIN0>>12)&1)==0))
		{
			
		   IOSET0=1<<17;						   
		   IOCLR0=1<<18;
		   r=1;	
		   z++;
		}
	else
		{
			r=0;
		}

	if(((IOPIN0>>10)&1)==0)
	{
		IOCLR0=LED_1;
	}				                      

	else if(((IOPIN0>>11)&1)==1)
	{
		IOCLR0=LED_1;
	}				                      
	
 	else
	 {
	 	
	 	 IOSET0=LED_1;
	  }
	 
	}
}
void UART_CONFIG(void)
{		     
	PINSEL0 |=0X50000;
	IODIR0 |= LED_1 | 1<<17 | 1<<18;
	U1LCR=0X83;
	U1DLL=97;
	U1DLM=0;
	U1LCR=0X03;
}
