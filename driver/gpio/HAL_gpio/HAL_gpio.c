#include "HAL_gpio.h"

/* HAL - Read pin input*/
uint32_t HAL_GPIO_ReadPin(GPIO_Type * base,PIN_name pin)
{
    assert(pin < 32U);
    return ((base->PDIR >> pin)&(1U));
}

/* HAL - Set direction*/
GPIO_Direct HAL_GPIO_SetDirection(GPIO_Type * base,PIN_name pin, GPIO_Direct direction)
{
    assert(pin < 32U);
    if(direction==GPIO_INPUT)
    {
        base->PDDR &= ~(1<<pin);
    }
    else
    {
        base->PDDR |= (1<<pin);
    }
    return direction;
}

/* HAL - Set pin output*/
void HAL_GPIO_WritePin(GPIO_Type * base,PIN_name pin, GPIO_PIN_status statusPIN)
{
    assert(pin < 32U);
    if(statusPIN==PIN_RESET)
    {
        base->PDOR &= ~(1 << pin);
    }
    else
    {
        base->PDOR |= (1 << pin);
    }
}

/* HAL - Toggle pin output*/
void HAL_GPIO_TogglePin(GPIO_Type * base,PIN_name pin)
{
    assert(pin < 32U);
    base->PTOR |= (1 << pin);
}


