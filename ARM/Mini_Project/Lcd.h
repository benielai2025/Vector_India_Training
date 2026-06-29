#ifndef LCD_H
#define LCD_H


void LCD_INIT(void);
void LCD_CMD(unsigned char);
void LCD_DATA(unsigned char);
void LCD_STR(unsigned char *);

#endif
