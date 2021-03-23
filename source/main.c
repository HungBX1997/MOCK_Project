#include "MKL46Z4.h"
#include "DRIVER_gpio.h"
#include "DRIVER_i2c.h"
#include "lcd.h"
#include "tea5767.h"
#include "stateMachine.h"
#include "clock.h"
#include "DRIVER_keyboard.h"
#include "DRIVER_core.h"

volatile static State_Keypad_Press  indexKey=NOT_KEY;
I2Cx_Master i2cMaster;
void main()
{
    stateProgram modeType;
    float freq=88.5;
    float freqActive[5]={0,0,0,0,0};
    int count=0;
    uint32_t statusMute=0;
    
    /* update core clock 8MHz*/
    updateClock_8MHz();
    
    /* Enable interrupt for keyboard*/
    DRV_EnableInterrupt(PORTC_PORTD_IRQn);
    
    /* Init Keyboard*/
    Init_Keypad();
    
    /* Init I2C0*/
    i2cMaster.base = I2C0;
    i2cMaster.baudRate_kbps=100;
    DRV_I2Cx_InitMaster(i2cMaster);
    
    /* Run radio with 89MHz */
    setFrequency(freq,statusMute);
    
    /* Send main screen to LCD*/
    modeType=modeMain();

    while(1)
    {
        /* Key 3 pressdown*/
        if(indexKey==KEY_3)
        {
            /* Check screen which is being displayed*/
            switch(modeType)
            {
            case RUN_FREQ_SELECTED:                               /* Keypad 3 in frequency selected mode*/
                count--;
                if(count<0)
                {
                    count=4;
                }
                setFrequency(freqActive[count],statusMute);
                LCD_RunFreqSelected_Screen(freqActive[count]);
                break;
            case SETUP_MODE:                                     /* Keypad 3 in set up mode*/
                modeType=modeRunFreqSelected(freqActive,count);
                break;
            case SELECT_CHANNEL:                                 /* Keypad 3 in select channel mode*/
                freq-=0.5;
                if(freq<89)freq=99.5;
                setFrequency(freq,statusMute);
                LCD_SelectChannelScreen(freq);
                break;
            }
            indexKey=NOT_KEY;
        }
        /* Key 2 pressdown*/
        if(indexKey==KEY_2)
        {
            switch(modeType)
            {
            case RUN_FREQ_SELECTED:
                freqActive[count]=0;
                setFrequency(freqActive[count],statusMute);
                LCD_RunFreqSelected_Screen(freqActive[count]);
                break;
            case SELECT_CHANNEL:                                 /* Keypad 2 in select channel mode*/
                if(count<5)
                {
                    modeSaveFreqCurrent(freq,freqActive,count);
                    count++;
                    DRV_Delay(500);
                    modeType=modeSelectChannel(freq);
                }
                else
                {
                    count=0;
                    LCD_Init();
                    LCD_Send_String("  Can't   Save  ");
                    DRV_Delay(500);
                    modeType=modeRunFreqSelected(freqActive,count);
                }
                break;
            case SETUP_MODE:                                      /* Keypad 2 in mute mode*/
                statusMute=!statusMute;
                modeMute(freq,statusMute);
                break;
            }
            indexKey=NOT_KEY;
        }
        /* Key 1 pressdown*/
        if(indexKey==KEY_1)
        {
            switch(modeType)
            {
            case MAIN:                                            /* Keypad 1 in main screen*/
                modeType=modeAutoSearch();
                break;
            case AUTO_SEARCHING:                                  /* Keypad 1 in auto search mode*/
                modeType=modeMain();
                break;
            case SETUP_MODE:                                       /* Keypad 1 in set up mode*/
                modeType=modeMain();
                break;
            case SELECT_CHANNEL:                                   /* Keypad 1 in select channel mode*/
                modeType=modeSetup();
                break; 
            case RUN_FREQ_SELECTED:                                 /* Keypad 1 in frequency selected mode*/
                modeType=modeSetup();
                break;
            }
            indexKey=NOT_KEY;
        }
        /* Key 4 pressdown*/
        if(indexKey==KEY_4)
        {
            switch(modeType)
            {
            case MAIN:                                              /* Keypad 4 in main screen*/
                modeType=modeSetup();
                break;
            case SETUP_MODE:                                        /* Keypad 4 in set up mode*/
                modeType=modeSelectChannel(freq);
                break;
            case SELECT_CHANNEL:                                    /* Keypad 4 in select channel mode*/
                freq+=0.5;
                if(freq>99.5)freq=89;
                setFrequency(freq,statusMute);
                LCD_SelectChannelScreen(freq);
                break;
            case RUN_FREQ_SELECTED:                                 /* Keypad 4 in frequency selected mode*/
                count++;
                if(count>4)
                {
                    count=0;
                }
                setFrequency(freqActive[count],statusMute);
                LCD_RunFreqSelected_Screen(freqActive[count]);
                break;
            }
            indexKey=NOT_KEY;
        }
    }
}

void PORTC_PORTD_IRQHandler()
{
    if(DRV_GetInterruptFlag(PORT_KEYBOARD,PIN_KEYBOARD_1))
    {
        /* Clear flag interrupt*/
        DRV_PORT_ClearInterruptFlag(PORT_KEYBOARD,PIN_KEYBOARD_1);
        indexKey=KEY_1;
    }
    if(DRV_GetInterruptFlag(PORT_KEYBOARD,PIN_KEYBOARD_2))
    {
        /* Clear flag interrupt*/
        DRV_PORT_ClearInterruptFlag(PORT_KEYBOARD,PIN_KEYBOARD_2);
        indexKey=KEY_2;
    }
    if(DRV_GetInterruptFlag(PORT_KEYBOARD,PIN_KEYBOARD_3))
    {
        /* Clear flag interrupt*/
        DRV_PORT_ClearInterruptFlag(PORT_KEYBOARD,PIN_KEYBOARD_3);
        indexKey=KEY_3;
    }
    if(DRV_GetInterruptFlag(PORT_KEYBOARD,PIN_KEYBOARD_4))
    {
        /* Clear flag interrupt*/
        DRV_PORT_ClearInterruptFlag(PORT_KEYBOARD,PIN_KEYBOARD_4);
        indexKey=KEY_4;
    }
}
/*
@EOF
*/
