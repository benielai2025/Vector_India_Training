#include <lpc21xx.h>
#include "delay.h"
#include "lcd.h"

#define IR ((IOPIN0>>10)&1)

typedef unsigned char u8;
typedef signed char   s8;
typedef unsigned short int  u16;
typedef signed short   int  s16;
typedef unsigned int  u32;
typedef signed   int  s32;
typedef float f32;
typedef double f64;

 struct can2
	{
	u32 id;
	u32 dlc;
	u32 rtr;
	u32 a_byte;

    }m1;


// CAN Initializing function....
void can_init(void)
{
  PINSEL1|=0X14000; // setting the pins 0.23 & 0.24 as RD2 And TD2...
 // VPBDIV=1; //PCLK=60MHz
C2MOD=0X01; //Reset mode..
AFMR=0X02; // Accepting the all msg without acceptance filtering..
C2BTR=0X001C001D; // setting the BRP Value..
C2MOD=0X00; //Normal mode...
}

void can_tx(void)
{
 m1.a_byte=IR; // assign the current count value to the a_byte..
                       
 C2TID1=m1.id;
 C2TFI1 &= ~(0xF << 16);
 C2TFI1|=(m1.dlc<<16);

if(m1.rtr==0)
{
 C2TFI1&=~(1<<30);
C2TDA1=m1.a_byte;
}
else
{
 C2TFI1|=(1<<30);
}
C2CMR=(1<<0)|(1<<5);// Start the transmission and selecting the transmit buffer 1...

 // waiting for the transmission to complete...
while(!(C2GSR&(1<<3))); // waiting for transmit buffer to complete..

}

 void tim_inter(void) __irq
{
    T1IR=0X01;

// Transmitting the count value for every 400ms....
can_tx();

VICVectAddr=0;
}
void timer_inter(void)
{
T1MR0=3550000-1;
T1MCR=0X03;


VICIntSelect=0;

VICVectCntl0=(0x20)|5;
VICVectAddr0=(unsigned int)tim_inter;

VICIntEnable=(1<<5);
T1TCR=0X02;
T1TCR=0X01;

}
  // CAN Transmitting function...

int main()
{
lcd_init();
can_init();
timer_inter();

m1.id=0x22; // id for IR node..
m1.rtr=0;
m1.dlc=1;
lcd_str("IR value:");  

while(1)
  {
  
   lcd_cmd(0xc0);
   lcd_str("IR:");
   lcd_int((IOPIN0>>10)&1);
   
   delay_ms(200);

   }

}

