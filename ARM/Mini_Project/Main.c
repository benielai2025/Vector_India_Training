#include<LPC21XX.H>
#include"Lcd.h"
#include"UART0.h"
#include"Delay.h"
#include"Transmit.h"

int main()
{
    LCD_INIT();
	UART0_CONFIG();

	LCD_CMD(0X80);
    LCD_STR("AGRI AUTOMATION");
	LCD_CMD(0XC0);
    LCD_STR("V25CE2P5");
	delay_millisecond(4000);
	
	transmit();

}

