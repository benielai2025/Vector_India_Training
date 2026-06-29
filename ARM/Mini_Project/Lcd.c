#include<LPC21XX.H>
#include"Lcd.h"
#include"Delay.h"

#define LCD_DB (15 << 14)
#define RS (1 << 8)
#define EN (1 << 9)

void LCD_INIT()
{
IODIR0 = LCD_DB | RS | EN;
LCD_CMD(0x01);
LCD_CMD(0x02);
LCD_CMD(0x0C);
LCD_CMD(0x28);
}

void LCD_CMD(unsigned char cmd)
{
IOCLR0 = LCD_DB;
IOSET0 = ((cmd&0xf0)<<10);
IOCLR0 = RS;
IOSET0 = EN;
delay_millisecond(2);
IOCLR0 = EN;

IOCLR0 = LCD_DB;
IOSET0 = ((cmd&0x0f)<<14);
IOCLR0 = RS;
IOSET0 = EN;
delay_millisecond(2);
IOCLR0 = EN;
}

void LCD_DATA(unsigned char data)
{
IOCLR0 = LCD_DB;
IOSET0 = ((data&0xf0) << 10);
IOSET0 = RS;
IOSET0 = EN;
delay_millisecond(2);
IOCLR0 = EN;

IOCLR0 = LCD_DB;
IOSET0 = ((data&0x0f) << 14);
IOSET0 = RS;
IOSET0 = EN;
delay_millisecond(2);
IOCLR0 = EN;
}

void LCD_STR(unsigned char *str)
{
int i;

for(i=0;str[i];i++)
{
LCD_DATA(str[i]);
}

}
