#ifndef UART0_H
#define UART0_H

void UART0_CONFIG(void);
void UART0_TX(unsigned char);
unsigned char UART0_RX();
void UART0_STR(const char *);

#endif
