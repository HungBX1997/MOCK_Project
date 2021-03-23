#include "stateMachine.h"
#include "lcd.h"
#include "MKL46Z4.h"
#include "tea5767.h"

stateProgram modeDefault()
{
    stateProgram status=DEFAULT;
    return status;
}

stateProgram modeMain()
{
    LCD_Main_Screen();
    return MAIN;
}

stateProgram modeAutoSearch()
{
    LCD_Search_Screen();
    scanFrequency(1);
    return AUTO_SEARCHING;
}

stateProgram modeSetup()
{
    LCD_Setup_Screen();
    return SETUP_MODE;
}

stateProgram modeSelectChannel(float freq)
{
    LCD_SelectChannelScreen(freq);
    return SELECT_CHANNEL;
}

stateProgram modeRunFreqSelected(float* freqCurrent,int count)
{
    LCD_RunFreqSelected_Screen(freqCurrent[count]);
    return RUN_FREQ_SELECTED;
}

void modeSaveFreqCurrent(float freq,float* freqCurrent,int count)
{
    char ch=count + '0';
    freqCurrent[count]=freq;
    LCD_Init();
    LCD_Send_Data(ch);
}

void modeMute(float freq,uint32_t statusMute)
{
    setFrequency(freq,statusMute);
}