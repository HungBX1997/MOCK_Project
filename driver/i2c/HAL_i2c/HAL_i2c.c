#include "HAL_i2c.h"


static void pause(void)
{
    int n;
    for(n=0; n<40; n++)
        asm("nop");
}

/*************************************************************
@brief: Set up port for I2C
@param: None
@return: None
**************************************************************/
static void HAL_I2C_SetupPort(void)
{  
#if I2C0_SELECT
    /* Enable clock for port*/
    EnableClockPort(PORT_I2C0);
    /* Set mux port as Alt2*/
    HAL_PORT_SetMuxMode(PORT_I2C0,PIN_I2C0_SCL,MuxAlt2);
    HAL_PORT_SetMuxMode(PORT_I2C0,PIN_I2C0_SDA,MuxAlt2);
#endif
#if I2C1_SELECT
    /* Enable clock for port*/
    EnableClockPort(PORT_I2C1);
    /* Set mux port as Alt2*/
    HAL_PORT_SetMuxMode(PORT_I2C1,PIN_I2C1_SCL,kPortMuxAlt2);
    HAL_PORT_SetMuxMode(PORT_I2C1,PIN_I2C1_SDA,kPortMuxAlt2);
#endif
}

/**********************************************************
@brief: HAL - Enable for I2C
@param: base of I2C
@return:  None
***********************************************************/
static inline void HAL_I2C_Enable(I2C_Type *base)
{
    base->C1 |= (1 << I2C_C1_IICEN_SHIFT);
}

/**********************************************************
@brief: HAL - Disable for I2C
@param: base of I2C
@return: None
***********************************************************/
static inline void HAL_I2C_Disable(I2C_Type * base)
{
    base->C1 &= ~(1 << I2C_C1_IICEN_SHIFT);
}

/**********************************************************
@brief: HAL - Set ddiirrection for I2C
@param1: base of I2C
@param2: 
         I2CReceive  : Receive data
         I2CSend     : Send data
@return: None
***********************************************************/
void HAL_I2C_SetDirMode(I2C_Type * base, I2C_Direction direction)
{
    if(direction==I2CSend)
    {
        base->C1 |= I2C_C1_TX_MASK;
    }
    else
    {
        base->C1 &= ~I2C_C1_TX_MASK;
    }
}

/**********************************************************
@brief: HAL - Set Baudrate for I2C
@param1: base of I2C
@param2: bus clock
@param3: baudrate user config
@return: None
***********************************************************/
static void HAL_SetBaurate(I2C_Type *base, uint32_t busClock, uint32_t baurate)
{
    uint32_t mult, i, multiplier, computedRate, absError;
    uint32_t hz = baurate * 1000u;
    uint32_t bestError = 0xffffffffu;
    uint32_t bestMult = 0u;
    uint32_t bestIcr = 0u;

    /* Search for the settings with the lowest error.
     * mult is the MULT field of the I2C_F register, and ranges from 0-2. It selects the
     * multiplier factor for the divider. */
    for (mult = 0u; (mult <= 2u) && (bestError != 0); ++mult)
    {
        multiplier = 1u << mult;

        /* Scan table to find best match.*/
        for (i = 0u; i < ARRAY_SIZE(I2CDividerTable); ++i)
        {
            computedRate = busClock / (multiplier * I2CDividerTable[i].sclDivider);
            absError = hz > computedRate ? hz - computedRate : computedRate - hz;

            if (absError < bestError)
            {
                bestMult = mult;
                bestIcr = I2CDividerTable[i].icr;
                bestError = absError;

                /* If the error is 0, then we can stop searching
                 * because we won't find a better match.*/
                if (absError == 0)
                {
                    break;
                }
            }
        }
    }
    base->F = 0;
    base->F |= (bestMult << I2C_F_MULT_SHIFT);
    base->F |= (bestIcr << I2C_F_ICR_SHIFT);
}

/* HAL - Init master*/
void HAL_I2Cx_InitMaster(I2C_Type *base,uint32_t baudrate)
{
#if I2C0_SELECT
    if(base==I2C0)
    {
        SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;
    }
#endif

#if I2C1_SELECT
    if(base==I2C1)
    {
        SIM->SCGC4 |= SIM_SCGC4_I2C1_MASK;
    }
#endif
    HAL_I2C_SetupPort();
    
    HAL_SetBaurate(base,4000000,baudrate);
    
    HAL_I2C_Enable(base);
    
}

/* HAL - Start*/
void HAL_I2Cx_Start(I2C_Type *base)
{
    base->C1 |= I2C_C1_TX_MASK;
    if(base->C1 & I2C_C1_MST_MASK)
    {
        base->C1 |= I2C_C1_RSTA_MASK;
    }
    else
    {
        base->C1 |= I2C_C1_MST_MASK;
    }
}

/* HAL - Stop*/
void HAL_I2Cx_Stop(I2C_Type *base)
{
    base->C1 &= ~I2C_C1_MST_MASK;
    base->C1 &= ~I2C_C1_TX_MASK;
}

/* HAL - GetAck*/
uint32_t HAL_I2C_GetAck(I2C_Type * base)
{
    uint32_t statusAck;
    if((base->S & I2C_S_RXAK_MASK) == 0)
        statusAck = 1;
    else
        statusAck = 0;
    return statusAck;
}

/* HAL - Disable*/
void HAL_I2Cx_Disable(I2C_Type *base)
{
    HAL_I2C_Disable(base);
}

/* Write data*/
void HAL_I2Cx_WriteData(I2C_Type *base,uint8_t data)
{
    base->D = data;
    while(HAL_I2C_GetAck(base)==0);
}

uint8_t HAL_I2Cx_ReadData(I2C_Type *base)
{
    return base->D;
}

/* HAL - Write block data*/
void HAL_I2Cx_MasterSendData(I2C_Type *base,uint8_t slaveAddress, uint8_t * bufData,uint32_t sizeData)
{
    uint32_t i=0;
    HAL_I2Cx_Start(base);
    HAL_I2Cx_WriteData(base,slaveAddress << 1);
    pause();
    for(i = 0; i < sizeData; ++i)
    {
        HAL_I2Cx_WriteData(base,bufData[i]);
        while(!(base->S & I2C_S_TCF_MASK));
    }
    HAL_I2Cx_Stop(base);
    pause();
}

void HAL_I2Cx_MasterReceiveData(I2C_Type *base,uint8_t slaveAddress, uint8_t * bufData,uint32_t sizeData)
{
    uint32_t i=0;
    HAL_I2Cx_Start(base);
    HAL_I2Cx_WriteData(base,(slaveAddress << 1)|(1U));
    pause();
    HAL_I2C_SetDirMode(base, I2CReceive);
    pause();
    for(i = 0; i < sizeData; ++i)
    {
        bufData[i] = HAL_I2Cx_ReadData(base);
    }
    HAL_I2Cx_Stop(base);
    pause();
}
