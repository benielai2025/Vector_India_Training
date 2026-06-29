#include<LPC21XX.H>
#include"Lcd.h"
#include"UART0.h"
#include"Delay.h"
#include"Receive.h"

#define SW 16

void transmit()
{   
    //LCD_INIT();
	//UART0_CONFIG();
    
    while(1)
    {
       if(((IOPIN1 >> SW)&1) == 1) 
       {
           delay_millisecond(200);
		   LCD_CMD(0x01);
		   LCD_CMD(0x80);
           LCD_STR("Soil Condition:");
           LCD_CMD(0xC0);
           LCD_STR("Soil is Dry");
           
           UART0_STR("AT\r\n");
           delay_millisecond(500);
    
           UART0_STR("AT+CMGF=1\r\n");
           delay_millisecond(500);
    
           UART0_STR("AT+CMGS=\"+918270626400\"\r\n");
           delay_millisecond(1000);
    
           UART0_STR("Soil is Dry");
    
           UART0_TX(0x1A);
           delay_millisecond(1000);

		   receive();
           
           while(((IOPIN1 >> SW)&1) == 1);
       }
    }
}


