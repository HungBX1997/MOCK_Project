#include "DRIVER_keyboard.h"
#include "DRIVER_gpio.h"
#include "board.h"

void Init_Keypad()
{
    Gpio_input_config input;
    
    input.portBase = PORT_KEYBOARD;
    input.gpioBase = GPIO_KEYBOARD;
    input.pinName = PIN_KEYBOARD_2;
    input.inputConfig.isPullEnable=true;
    input.inputConfig.pullSelect=PullUp;
    input.inputConfig.interrupt = IntFallingEdge;
    DRV_InitGPIO_Input(input);
    
    input.portBase = PORT_KEYBOARD;
    input.gpioBase = GPIO_KEYBOARD;
    input.pinName = PIN_KEYBOARD_1;
    input.inputConfig.isPullEnable=true;
    input.inputConfig.pullSelect=PullUp;
    input.inputConfig.interrupt = IntFallingEdge;
    DRV_InitGPIO_Input(input);
    
    input.portBase = PORT_KEYBOARD;
    input.gpioBase = GPIO_KEYBOARD;
    input.pinName = PIN_KEYBOARD_3;
    input.inputConfig.isPullEnable=true;
    input.inputConfig.pullSelect=PullUp;
    input.inputConfig.interrupt = IntFallingEdge;
    DRV_InitGPIO_Input(input);
    
    input.portBase = PORT_KEYBOARD;
    input.gpioBase = GPIO_KEYBOARD;
    input.pinName = PIN_KEYBOARD_4;
    input.inputConfig.isPullEnable=true;
    input.inputConfig.pullSelect=PullUp;
    input.inputConfig.interrupt = IntFallingEdge;
    DRV_InitGPIO_Input(input);
}
