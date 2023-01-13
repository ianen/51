#ifndef __LCD1602_H__
#define __LCD1602_H__

void LCD_Init(void);
void LCD_ShowChar(unsigned Line,unsigned char Column,unsigned char Char);
void LCD_ShowString(unsigned Line,unsigned char Column,unsigned char String[]);
#endif