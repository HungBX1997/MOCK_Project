#ifndef __LCD_H_
#define __LCD_H_
#include <stdint.h>

#define ADD_PCF8574  (0x27)

void DRV_Delay(uint32_t miliSecond);
void LCD_Send_CMD(char cmd);
void LCD_Init();
void LCD_Send_Data(char data);
void LCD_Send_String(char *str);
void LCD_goto_XY (int row, int col);
void LCD_Main_Screen();
void LCD_Search_Screen();
void LCD_Setup_Screen();
void LCD_RunFreqSelected_Screen(float freq);
void LCD_SelectChannelScreen(float freq);
void LCD_tranDataFreq(float freq);
#endif /*__LCD_H_*/