#include "DRIVER_core.h"

void DRV_EnableInterrupt(IRQn_Type number)
{
    NVIC_EnableIRQ(number);
}

void DRV_DisableInterrupt(IRQn_Type number)
{
    NVIC_DisableIRQ(number);
}

void DRV_SetPriority(IRQn_Type number, uint32_t priority)
{
    NVIC_SetPriority(number,priority);
}

void DRV_SetPending(IRQn_Type number)
{
    NVIC_SetPendingIRQ(number);
}

void DRV_ClearPending(IRQn_Type number)
{
    NVIC_ClearPendingIRQ(number);
}