#include "HAL_port.h"

/* Enable Clock for PORT*/
void EnableClockPort(PORT_Type *port_base)
{
    if(port_base==PORTA)
    {
        SIM->SCGC5 |= (1<<9);
    }
    if(port_base==PORTB)
    {
        SIM->SCGC5 |= (1<<10);
    }
    if(port_base==PORTC)
    {
        SIM->SCGC5 |= (1<<11);
    }
    if(port_base==PORTD)
    {
        SIM->SCGC5 |= (1<<12);
    }
    if(port_base==PORTE)
    {
        SIM->SCGC5 |= (1<<13);
    }
}

/* Set pull up or pull down for PORT*/
void HAL_PORT_SetPullMode(PORT_Type * base,PIN_name pin,PORT_pull pullSelect)
{
    assert(pin < 32U);
    if(pullSelect==PullDown)
    {
        base->PCR[pin] &= ~(1<<0U);
    }
    else
    {
        base->PCR[pin] |= (1<<0U);
    }
}

/* Confirm enable pull or no pull*/
void HAL_PORT_PullEnable(PORT_Type * base,PIN_name pin,bool isPullEnabled)
{
    assert(pin < 32U);
    if(isPullEnabled==false)
    {
        base->PCR[pin] &= ~(1<<1U);
    }
    else
    {
        base->PCR[pin] |= (1<<1U);
    }
}
   
/* Set mode for PORT*/
void HAL_PORT_SetMuxMode(PORT_Type * base,PIN_name pin,PORT_MUX mux)
{    
    assert(pin < 32U);
    base->PCR[pin] &= ~(7<<8);
    switch(mux)
    {
    case PinDisabled:
      break;
    case MuxAsGpio:
      base-> PCR[pin] |= (1<<8);
      break;
    case MuxAlt2:
      base-> PCR[pin] |= (2<<8);
      break;
    case MuxAlt3:
      base-> PCR[pin] |= (3<<8);
      break;
    case MuxAlt4:
      base-> PCR[pin] |= (4<<8);
      break;
    case MuxAlt5:
      base-> PCR[pin] |= (5<<8);
      break;
    case MuxAlt6:
      base-> PCR[pin] |= (6<<8);
      break;
    case MuxAlt7:
      base-> PCR[pin] |= (7<<8);
      break;
    }
}

/* Config interrupt for PIN*/
 void HAL_PORT_SetPinIntMode(PORT_Type * base,PIN_name pin,PORT_Interrupt intConfig)
{
    assert(pin < 32U);
    base->PCR[pin] &= ~(0xF<<16U);
    switch(intConfig)
    {
    case IntDisabled:
      break;
    case DmaRisingEdge:
      base->PCR[pin] |= (DmaRisingEdge<<16U);
      break;
    case DmaFallingEdge:
      base->PCR[pin] |= (DmaFallingEdge<<16U);
      break;
    case DmaEitherEdge:
      base->PCR[pin] |= (DmaEitherEdge<<16U);
      break;
    case IntLogicZero:
      base->PCR[pin] |= (IntLogicZero<<16U);
      break;
    case IntRisingEdge:
      base->PCR[pin] |= (IntRisingEdge<<16U);
      break;
    case IntFallingEdge:
      base->PCR[pin] |= (IntFallingEdge<<16U);
      break;
    case IntEitherEdge:
      base->PCR[pin] |= (IntEitherEdge<<16U);
      break;
    case IntLogicOne:
      base->PCR[pin] |= (IntLogicOne<<16U);
      break;
    }   
}

/* Get interrupt mode */
 PORT_Interrupt HAL_PORT_GetPinIntMode(PORT_Type * base, PIN_name pin)
{
    assert(pin < 32U);

    return (PORT_Interrupt)0;
}

/* Get interrupt in pending*/
 bool HAL_PORT_IsPinIntPending(PORT_Type * base, PIN_name pin)
{
    assert(pin < 32U);
    
    return false;
}

/* Clear flag of interrupt PIN*/
 void HAL_PORT_ClearPinIntFlag(PORT_Type * base, PIN_name pin)
{
    assert(pin < 32U);
    if(base->PCR[pin] & PORT_PCR_ISF_MASK)
    {
        base->PCR[pin] |= PORT_PCR_ISF_MASK;
    }    
}

/* Read status of flag */
uint32_t HAL_PORT_GetPortIntFlag(PORT_Type * base,PIN_name pin)
{
    
    return ((base->PCR[pin]>>24)&1U);
}

void HAL_PORT_SetLowGlobalPinCtrl(PORT_Type * base, uint16_t lowPinSelect, uint16_t config)
{
      
}
void HAL_PORT_SetHighGlobalPinCtrl(PORT_Type * base, uint16_t highPinSelect, uint16_t config)
{
    
}