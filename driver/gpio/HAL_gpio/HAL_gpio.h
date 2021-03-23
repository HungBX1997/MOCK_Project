#ifndef __HAL_GPIO_H
#define __HAL_GPIO_H
 
#include "MKL46Z4.h"
#include "HAL_port.h"
#include <assert.h>
#include <stdint.h>
#include <stdbool.h>

/***********************************************************
@: Logic level for Pin
************************************************************/
typedef enum {
    PIN_RESET =0,
    PIN_SET   =1
}GPIO_PIN_status;

/***********************************************************
@: Direction for Pin
************************************************************/
typedef enum
{
    GPIO_INPUT=0,
    GPIO_OUTPUT
}GPIO_Direct;

/***********************************************************
@brief: Read Logic level for Pin
@param1: base of GPIOx (x as A..E)
@param2: PIN name
@return: logic level of pin
************************************************************/
uint32_t HAL_GPIO_ReadPin(GPIO_Type * base,PIN_name pin);

/***********************************************************
@brief: Set direction for pin
@param1: base of GPIOx (x as A..E)
@param2: PIN name
@param3: direction for pin
@return: INPUT or OUTPUT
************************************************************/
GPIO_Direct HAL_GPIO_SetDirection(GPIO_Type * base,PIN_name pin, GPIO_Direct direction);

/***********************************************************
@brief: Set Logic level for Pin
@param1: base of GPIOx (x as A..E)
@param2: PIN name
@param3: logic level   
@return: logic level of pin
************************************************************/
void HAL_GPIO_WritePin(GPIO_Type * base,PIN_name pin,GPIO_PIN_status statusPIN);

/***********************************************************
@brief: Toggle Logic level
@param1: base of GPIOx (x as A...E)
@param2: PIN name
@return: None 
************************************************************/
void HAL_GPIO_TogglePin(GPIO_Type * base,PIN_name pin);
#endif /* __HAL_GPIO_H*/