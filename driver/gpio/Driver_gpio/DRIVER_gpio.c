#include "DRIVER_gpio.h"

/* Driver init GPIO input or output*/
void DRV_InitGPIO(Gpio_input_config *inputPin,
                  Gpio_output_config *outputPin)
{
    if(inputPin)
    {
        while(inputPin->pinName != GPIO_PIN_RANGE)
        {
            DRV_InitGPIO_Input(*inputPin++);
        }
    }
    if(outputPin)
    {
        while(outputPin->pinName != GPIO_PIN_RANGE)
        {
            DRV_InitGPIO_Output(*outputPin++);
        }
    }
}

/* Driver init GPIO input*/
uint32_t DRV_InitGPIO_Input(Gpio_input_config inputPin)
{
    EnableClockPort(inputPin.portBase);
    
    HAL_PORT_SetMuxMode(inputPin.portBase, inputPin.pinName, MuxAsGpio);
    
    HAL_GPIO_SetDirection(inputPin.gpioBase, inputPin.pinName, GPIO_INPUT);
    
    HAL_PORT_PullEnable(inputPin.portBase, inputPin.pinName, inputPin.inputConfig.isPullEnable);
    
    HAL_PORT_SetPullMode(inputPin.portBase, inputPin.pinName, inputPin.inputConfig.pullSelect);
    
    HAL_PORT_SetPinIntMode(inputPin.portBase, inputPin.pinName, inputPin.inputConfig.interrupt);
    
    return 0;
}

/* Driver init GPIO output*/
uint32_t DRV_InitGPIO_Output(Gpio_output_config outputPin)
{
    EnableClockPort(outputPin.portBase);
    
    HAL_PORT_SetMuxMode(outputPin.portBase, outputPin.pinName, MuxAsGpio);
    
    HAL_GPIO_SetDirection(outputPin.gpioBase, outputPin.pinName, GPIO_OUTPUT);
    
    return 0;
}

/* Driver Set direction for pin*/
uint32_t DRV_SetPinDirection(GPIO_Type * base,
                         PIN_name pin, 
                         GPIO_Direct direction)
{
    HAL_GPIO_SetDirection(base, pin, direction);
    return 0;
}

/* Set logic level for pin*/
void DRV_GPIO_WritePin(GPIO_Type * base,
                       PIN_name pin, 
                       GPIO_PIN_status statusPIN)
{
    HAL_GPIO_WritePin(base, pin, statusPIN);
}

/* Toggle logic level for pin*/
void DRV_GPIO_TogglePin(GPIO_Type * base, PIN_name pin)
{
    HAL_GPIO_TogglePin(base, pin);
}

/* Read logic level of pin*/
GPIO_PIN_status DRV_GPIO_ReadPin(GPIO_Type * base, PIN_name pin)
{
    GPIO_PIN_status statePin=PIN_RESET;
    if((base->PDIR >> pin) & (1U))
    {
           statePin=PIN_SET;
    }
    return statePin;
}

/* Clear flag of interrupt*/
void DRV_PORT_ClearInterruptFlag(PORT_Type * base, PIN_name pin)
{
    HAL_PORT_ClearPinIntFlag(base, pin);
}

/* Read status of flag*/
uint32_t DRV_GetInterruptFlag(PORT_Type * base, PIN_name pin)
{
    return HAL_PORT_GetPortIntFlag(base,pin);
}
