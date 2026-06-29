#include<LPC21XX.H>

void delay_second(unsigned int second)
{
T0PR  = 15000000 - 1;
T0TCR =	0x01;
while(T0TC < second);
T0TCR =	0x03;
T0TCR =	0x00;
}

void delay_millisecond(unsigned int millisecond)
{
T0PR  = 15000 - 1;
T0TCR =	0x01;
while(T0TC < millisecond);
T0TCR =	0x03;
T0TCR =	0x00;
}
