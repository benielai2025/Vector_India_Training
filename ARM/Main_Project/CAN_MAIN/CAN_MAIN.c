#include <lpc21xx.h>
#include "delay.h"
#include "lcd.h"
#define ID_TEMP 0x11
#define ID_IR   0x22

#define IR_LED   18     // LED for IR status
#define TEMP_LED 19     // LED for temperature alert

#define TEMP_HIGH 20   //Temp warning value

typedef unsigned char u8;
typedef signed char   s8;
typedef unsigned short int  u16;
typedef signed short   int  s16;
typedef unsigned int  u32;
typedef signed   int  s32;
typedef float f32;
typedef double f64;
 
typedef struct can2
{
u32 id;
u32 dlc;
u32 rtr;
u32 data;
}can_msg;

void can_init(void)
{
PINSEL1|=0X14000; 
C2MOD=0X01; 
AFMR=0X02; // Accepting the all msg without acceptance filtering..
C2BTR=0X001C001D; // setting the BRP Value..
C2MOD=0X00; //Normal mode...
}

void can_rx(can_msg *temp_msg, can_msg *ir_msg)
{
    if(C2GSR & 0x01)   // RX buffer full
    {
        u32 id = C2RID;
        u32 data = C2RDA;
        if(id == ID_TEMP)
        {
            temp_msg->data = data;
        }
        else if(id == ID_IR)
        {
            ir_msg->data = data;
        }
        C2CMR = (1<<2);   // Release RX buffer
    }
}

int main()
{
    can_msg temp_node = {0}, ir_node = {0};
lcd_init();
can_init();
IODIR0 |= (1 << IR_LED) | (1 << TEMP_LED);
lcd_str("RAILWAY MONITOR");
  while(1)
{

        can_rx(&temp_node, &ir_node);

if(ir_node.data == 0)          // IR = 0
{
IOCLR0 = (1 << IR_LED);    // LED ON
lcd_cmd(0xc0);
lcd_str("FIRE");
}
        else
{
            IOSET0 = (1 << IR_LED);    // LED OFF
lcd_cmd(0xc0);
lcd_str("SAFE");
}

        if(temp_node.data > TEMP_HIGH)   // High temperature
{
            IOCLR0 = (1 << TEMP_LED);    // LED ON
lcd_cmd(0xd4);
lcd_str("HIGH TEMP");
}
        else
{
 IOSET0 = (1 << TEMP_LED);    // LED OFF
lcd_cmd(0xd4);
lcd_str("LOW TEMP");
}
}
}
