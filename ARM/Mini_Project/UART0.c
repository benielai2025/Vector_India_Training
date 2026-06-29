#include<LPC21XX.H>

void UART0_CONFIG()
{
PINSEL0 |= 0x5;
U0LCR = 0x83;
U0DLL = 97;
U0DLM = 0;
U0LCR = 0x03;
}

void UART0_TX(unsigned char d)
{
    while ((U0LSR & (1 << 5)) == 0);
    U0THR = d;
}

unsigned char UART0_RX(void)
{
    while ((U0LSR & 0x01) == 0); 
    return U0RBR;                
}

void UART0_STR(const char *str)
{
int i;

    for(i=0;str[i];i++)
	UART0_TX(str[i]);
}
