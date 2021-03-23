#ifndef _CORE_H_
#define _CORE_H_
#include "MKL46Z4.h"
#include <stdint.h>

void DRV_EnableInterrupt(IRQn_Type number);
void DRV_DisableInterrupt(IRQn_Type number);
void DRV_SetPriority(IRQn_Type number, uint32_t priority);
void DRV_SetPending(IRQn_Type number);
void DRV_ClearPending(IRQn_Type number);
#endif /* _CORE_H_*/