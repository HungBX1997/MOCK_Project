#ifndef __DRIVER_GPIO_H
#define __DRIVER_GPIO_H
 
#include "MKL46Z4.h"
#include "HAL_gpio.h"
#include "HAL_port.h"
#include "board.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#define GPIO_PIN_RANGE (32U)
/****************************************************
@: Define state for init GPIO
*****************************************************/
typedef enum
{
    Success =0,
    Error
}InitGPIO_State;


/****************************************************
@: Define GPIO Input
*****************************************************/
typedef struct 
{
    bool isPullEnable;
    PORT_pull pullSelect;
    PORT_Interrupt interrupt;
}Gpio_Input;


/****************************************************
@: Define GPIO Output
*****************************************************/
typedef struct 
{
    uint32_t outputLogic;  
}Gpio_Output;


/****************************************************
@: Define Pin for GPIO InPut
*****************************************************/
typedef struct
{
    PORT_Type *portBase;
    GPIO_Type *gpioBase;
    PIN_name pinName;
    Gpio_Input inputConfig;
}Gpio_input_config;


/****************************************************
@: Define Pin for GPIO OutPut
*****************************************************/
typedef struct
{
    PORT_Type *portBase;
    GPIO_Type *gpioBase;
    PIN_name pinName;
    Gpio_Output outputConfig;
}Gpio_output_config;


/****************************************************
@brief: Init GPIO input(output)
@param1: inputPin for Init GPIO as Input
@param2: outputPin for Init GPIO as Output
@return: None
*****************************************************/
void DRV_InitGPIO(Gpio_input_config *inputPin,
                  Gpio_output_config *outputPin);


/****************************************************
@@brief: Init GPIO input
@param1: inputPin for Init GPIO as Input
@return: GPIO InitState
*****************************************************/
uint32_t DRV_InitGPIO_Input(Gpio_input_config inputPin);


/****************************************************
@brief: Init GPIO out
@param1: putputPin for Init GPIO as output
@return: GPIO InitState
*****************************************************/
uint32_t DRV_InitGPIO_Output(Gpio_output_config outputPin);


/****************************************************
@brier: Set PIN Direction for GPIO
@param1: base of GPIOx (x as A...E). 
@param2: PIN name for GPIO.
@param3: Direction of PIN input or output
@return: GPIO InitState
*****************************************************/
uint32_t DRV_SetPinDirection(GPIO_Type * base,
                         PIN_name pin, 
                         GPIO_Direct direction);


/****************************************************
@brier: Set logic level of PIN as 1 or 0.
@param1: base of GPIOx (x as A...E). 
@param2: PIN name for GPIO.
@param3: Logic level 
         PIN_SET: Set logic level of PIN as 1
         PIN_RESET: Set logic level of PIN as 0
@return: None
*****************************************************/
void DRV_GPIO_WritePin(GPIO_Type * base,
                       PIN_name pin, 
                       GPIO_PIN_status statusPIN);


/****************************************************
@brier: Toggle logic level of PIN
@param1: base of GPIOx (x as A...E). 
@param2: PIN name for GPIO.
@return: None
*****************************************************/
void DRV_GPIO_TogglePin(GPIO_Type * base, PIN_name pin);


/****************************************************
@brier: Read logic level of PIN
@param1: base of GPIOx (x as A...E). 
@param2: PIN name for GPIO.
@return: Logic level of PIN
*****************************************************/
GPIO_PIN_status DRV_GPIO_ReadPin(GPIO_Type * base, PIN_name pin);


/****************************************************
@brier: Clear flag for external interrupt
@param1: base of PORTx (x as A...E). 
@param2: PIN name for GPIO.
@return: None
*****************************************************/
void DRV_PORT_ClearInterruptFlag(PORT_Type * base, PIN_name pin);


/****************************************************
@brier: Read state flag for external interrupt
@param1: base of PORTx (x as A...E). 
@param2: PIN name for GPIO.
@return: state flag
*****************************************************/
uint32_t DRV_GetInterruptFlag(PORT_Type * base, PIN_name pin);
#endif /* __DRIVER_GPIO_H*/