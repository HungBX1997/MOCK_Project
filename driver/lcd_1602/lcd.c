#include "lcd.h"
#include "DRIVER_i2c.h"

extern I2Cx_Master i2cMaster;
void DRV_Delay(uint32_t time)
{
    uint32_t i;
    for(i=0;i<time*2100;i++)
    {
        __asm("nop");
    }
}

void LCD_Init()
{
    LCD_Send_CMD (0x33); /* set 4-bits interface */
    LCD_Send_CMD (0x32);
    LCD_Send_CMD (0x28); /* start to set LCD function */
    LCD_Send_CMD (0x01); /* clear display */
    LCD_Send_CMD (0x06); /* set entry mode */
    LCD_Send_CMD (0x0c); /* set display to on */
    LCD_Send_CMD (0x02); /* move cursor to home and set data address to 0 */
    LCD_Send_CMD (0x80);
}

void LCD_Send_CMD(char cmd)
{
    char data_u, data_l;
    uint8_t data_t[4];
    data_u = (cmd&0xf0);
    data_l = ((cmd<<4)&0xf0);
    data_t[0] = data_u|0x0C;
    data_t[1] = data_u|0x08;
    data_t[2] = data_l|0x0C;
    data_t[3] = data_l|0x08;
#if I2C0_SELECT
    DRV_I2Cx_MasterSendData(i2cMaster.base,ADD_PCF8574,data_t,4);
#endif
#if I2C1_SELECT
    DRV_I2Cx_MasterSendData(i2cMaster.base,ADD_PCF8574,data_t,4);
#endif
}

void LCD_Send_Data(char data)
{
    char data_u, data_l;
    uint8_t data_t[4];
    data_u = (data&0xf0);
    data_l = ((data<<4)&0xf0);
    data_t[0] = data_u|0x0D;
    data_t[1] = data_u|0x09;
    data_t[2] = data_l|0x0D;
    data_t[3] = data_l|0x09;
#if I2C0_SELECT
    DRV_I2Cx_MasterSendData(i2cMaster.base,ADD_PCF8574,data_t,4);
#endif
#if I2C1_SELECT
    DRV_I2Cx_MasterSendData(i2cMaster.base,ADD_PCF8574,data_t,4);
#endif
}

void LCD_Send_String(char *str)
{
    while (*str) LCD_Send_Data(*str++);
}

void LCD_goto_XY (int row, int col)
{
    uint8_t pos_Addr;
    if(row == 1)
    {
        pos_Addr = 0x80 + row - 1 + col;
    }
    else
    {
        pos_Addr = 0x80 | (0x40 + col);
    }
    LCD_Send_CMD(pos_Addr);
}

void LCD_Main_Screen()
{
    LCD_Init();
    LCD_Send_String("    FM RADIO");
    LCD_goto_XY(2,0);    
    LCD_Send_String("AUTO/SE    SETUP");
}

void LCD_Setup_Screen()
{
    LCD_Init();
    LCD_Send_String("   SETUP MODE");
    LCD_goto_XY(2,0);
    LCD_Send_String("<- MUTE RUN SCAN");
}

void LCD_Search_Screen()
{
    LCD_Init();
    LCD_Send_String("SEARCHING...");
    LCD_goto_XY(2,0);
    LCD_Send_String("<-");
}

void LCD_SelectChannelScreen(float freq)
{
    LCD_Init();
    LCD_Send_String(" Tan So:");
    LCD_tranDataFreq(freq);
    LCD_Send_String("MHz ");
    LCD_goto_XY(2,0);
    LCD_Send_String("<-  SAVE  F-  F+");
}

void LCD_tranDataFreq(float freq)
{
    int i;
    char ch;
    uint32_t a[3];
    uint32_t b = (uint32_t)(freq * 10);
    a[0]=b/100;
    a[1]=(b-a[0]*100)/10;
    a[2]=(b-a[0]*100-a[1]*10);
    for(i=0;i<3;i++)
    {
        ch=a[i]+'0';
        LCD_Send_Data(ch);
        if(i==1)
        {
            LCD_Send_Data('.');
        }
    }
}

void LCD_RunFreqSelected_Screen(float freq)
{
    LCD_Init();
    LCD_Send_String("FM RADIO:");
    LCD_tranDataFreq(freq);
    LCD_Send_String("MHz ");
    LCD_goto_XY(2,0);
    LCD_Send_String("<-  CLEAR  F- F+");
}