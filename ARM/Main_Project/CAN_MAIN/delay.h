#include <lpc21xx.h>
void delay_sec(int sec)
{
 T0PR=15000000-1;
 T0TCR=0X01;
 while(T0TC<sec);
 T0TCR=0X03;
 T0TCR=0X00;
}
void delay_ms(int ms)
{
 T0PR=15000-1;
 T0TCR=0X01;
 while(T0TC<ms);
 T0TCR=0X03;
 T0TCR=0X00;
}
void delay_mcs(int mcs)
{
 T0PR=15-1;
 T0TCR=0X01;
 while(T0TC<mcs);
 T0TCR=0X03;
 T0TCR=0X00;
}
