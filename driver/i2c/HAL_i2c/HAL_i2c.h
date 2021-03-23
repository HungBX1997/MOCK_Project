#ifndef _HAL_I2C_H
#define _HAL_I2C_H

#include "MKL46Z4.h"
#include "HAL_port.h"
#include "board.h"

#define ARRAY_SIZE(x)  (sizeof(x)/sizeof((x)[0]))     /* Dimension of array*/

/*************************************************************************
@: I2C -  Status
**************************************************************************/
typedef enum  {
    I2C_Success            = 0x0U, 
    I2C_Fail               = 0x1U, 
} I2C_Status;

/*************************************************************************
@: I2C -  Flag
**************************************************************************/
typedef enum {
    I2CTransferComplete = I2C_S_TCF_MASK,
    I2CAddressAsSlave   = I2C_S_IAAS_SHIFT,
    I2CBusBusy          = I2C_S_BUSY_SHIFT,
    I2CArbitrationLost  = I2C_S_ARBL_SHIFT,
    I2CAddressMatch     = I2C_S_RAM_SHIFT,
    I2CSlaveTransmit    = I2C_S_SRW_SHIFT,
    I2CInterruptPending = I2C_S_IICIF_SHIFT,
    I2CReceivedNak      = I2C_S_RXAK_MASK 
} I2C_Status_Flag;

/*************************************************************************
@: I2C -  Direction
**************************************************************************/
typedef enum  {
    I2CReceive = 0U,   
    I2CSend    = 1U    
} I2C_Direction;

/*************************************************************************
@: I2C -  Baudrate
**************************************************************************/
typedef struct  {
    uint8_t icr;            
    uint16_t sclDivider;  
} I2CDividerTableEntry;
/*************************************************************************
@: I2C -  Table ICR-Divider
**************************************************************************/
static const I2CDividerTableEntry I2CDividerTable[] = {
        /* ICR  Divider*/
        { 0x00, 20 },
        { 0x01, 22 },
        { 0x02, 24 },
        { 0x03, 26 },
        { 0x04, 28 },
        { 0x05, 30 },
        { 0x09, 32 },
        { 0x06, 34 },
        { 0x0a, 36 },
        { 0x07, 40 },
        { 0x0c, 44 },
        { 0x10, 48 },
        { 0x11, 56 },
        { 0x12, 64 },
        { 0x0f, 68 },
        { 0x13, 72 },
        { 0x14, 80 },
        { 0x15, 88 },
        { 0x19, 96 },
        { 0x16, 104 },
        { 0x1a, 112 },
        { 0x17, 128 },
        { 0x1c, 144 },
        { 0x1d, 160 },
        { 0x1e, 192 },
        { 0x22, 224 },
        { 0x1f, 240 },
        { 0x23, 256 },
        { 0x24, 288 },
        { 0x25, 320 },
        { 0x26, 384 },
        { 0x2a, 448 },
        { 0x27, 480 },
        { 0x2b, 512 },
        { 0x2c, 576 },
        { 0x2d, 640 },
        { 0x2e, 768 },
        { 0x32, 896 },
        { 0x2f, 960 },
        { 0x33, 1024 },
        { 0x34, 1152 },
        { 0x35, 1280 },
        { 0x36, 1536 },
        { 0x3a, 1792 },
        { 0x37, 1920 },
        { 0x3b, 2048 },
        { 0x3c, 2304 },
        { 0x3d, 2560 },
        { 0x3e, 3072 },
        { 0x3f, 3840 }
    };

/*************************************************************************
@brief:I 2C -  Init master
@param1: base of I2C
@param2: baudrate for I2C
@return: None
**************************************************************************/
void HAL_I2Cx_InitMaster(I2C_Type *base,uint32_t baudrate);

/*************************************************************************
@brief: I2C - Set direction
@param1: base of I2C
@param2: direction of I2C
@return: None
**************************************************************************/
void HAL_I2C_SetDirMode(I2C_Type * base, I2C_Direction direction);

/*************************************************************************
@brief: I2C -  Init Start
@param1: base of I2C
@return: None 
**************************************************************************/
void HAL_I2Cx_Start(I2C_Type *base);

/*************************************************************************
@brief: I2C -  Init Stop
@param1: base of I2C
@return: None
**************************************************************************/
void HAL_I2Cx_Stop(I2C_Type *base);

/*************************************************************************
@brief: I2C -  Stop
@param1: base of I2C
@return: None
**************************************************************************/
void HAL_I2Cx_Disable(I2C_Type *base);

/*************************************************************************
@brief: I2C -  Write 1 byte data
@param1: base of I2C
@param2: 1 byte data
@return: None
**************************************************************************/
void HAL_I2Cx_WriteData(I2C_Type *base,uint8_t data);

/*************************************************************************
@brief: I2C -  Read 1 byte data
@param1: base of I2C
@param2: 1 byte data
@return: None
**************************************************************************/
uint8_t HAL_I2Cx_ReadData(I2C_Type *base);

/*************************************************************************
@brief: I2C -  Get ACK
@param1: base of I2C
@return: None
**************************************************************************/
uint32_t HAL_I2C_GetAck(I2C_Type * base);

/*************************************************************************
@brief: I2C -  Master Send data
@param1: base of I2C
@param2: address of slave
@param2: the first byte of block data
@param3: size of block data
@return: None
**************************************************************************/
void HAL_I2Cx_MasterSendData(I2C_Type *base,uint8_t slaveAddress, uint8_t * bufData,uint32_t sizeData);

/*************************************************************************
@brief: I2C -  Master Read data
@param1: base of I2C
@param2:adddresss of slave
@param2: the first byte of block data
@param3: size of block data
@return: None
**************************************************************************/
void HAL_I2Cx_MasterReceiveData(I2C_Type *base,uint8_t slaveAddress, uint8_t * bufData,uint32_t sizeData);
#endif /*_HAL_I2C_H*/
