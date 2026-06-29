#include<lpc21xx.h>
#include<string.h>
#include"UART0.h"
#include"LCD.h"
#include"Delay.h"

#define MOTOR (1 << 23)
			  
void receive()
{
    char buffer[256], ch; // Buffer to store the received SMS
    int index = 0, startmsg = 0; // Flag to indicate the start of the message

    //LCD_INIT();
    

    IODIR1 |= MOTOR;
    IOCLR1  = MOTOR;

    //LCD_CMD(0XC0);
    //LCD_STR("V25CE2P5");
	//delay_millisecond(4000);

    //LCD_CMD(0X80);
    //LCD_STR("AGRI AUTOMATION");

    // Initialize GSM module
	//UART0_CONFIG();
    UART0_STR("AT\r\n"); // Test AT communication
    delay_millisecond(1000);

    UART0_STR("AT+CMGF=1\r\n"); // Set SMS mode to text
    delay_millisecond(1000);

    UART0_STR("AT+CNMI=1,2,0,0,0\r\n"); // Enable SMS notifications
    delay_millisecond(1000);

    // Send SMS

    UART0_STR("AT+CMGS=\"+918270626400\"\r\n"); // Replace with your mobile number
    delay_millisecond(1000);

    UART0_STR("WAITING FOR SMS"); // Message content

	LCD_CMD(0X01);
	LCD_CMD(0X80);
	LCD_STR("WAITING FOR SMS");

    UART0_TX(0x1A); // Send Ctrl+Z to send SMS
    delay_millisecond(1000);

    // Wait for SMS and read it

    while (1)
    {
        ch = UART0_RX(); // Read a character from UART
		if(ch == '\n' || ch == '\r')
		{  
            if(index == 0)
	        continue; // Ignore empty lines
		 
            buffer[index] = '\0'; // Null-terminate the string
		 
            if(strstr(buffer, "+CMT:")!=0)
		    {
		      // SMS header detected, next line contains the actual message		 

		      startmsg = 1;
              index = 0; // Reset index for storing the message
              continue;
            }

            if(startmsg == 1)
            {
                // Message received after header

                UART0_STR("Received SMS: ");
				UART0_STR(buffer); // Display the received SMS

				LCD_CMD(0X01);
				LCD_CMD(0x80);// display on LCD

				LCD_STR((unsigned char *)buffer);

                UART0_STR("\r\n");

				if(strstr(buffer, "motoron"))// Alarm control
		        {
				IOSET1 = MOTOR;
			    delay_millisecond(300);
		        }
		        else if(strstr(buffer, "motoroff"))
		        {
			    IOCLR1 = MOTOR;
			    delay_millisecond(300);
		        }

                startmsg = 0; // Reset flag
            }
            index = 0; // Reset buffer index for next line
        }
        else if (index < sizeof(buffer) - 1)
        {
            buffer[index++] = ch; // Store character in buffer
        }
    }
}  




