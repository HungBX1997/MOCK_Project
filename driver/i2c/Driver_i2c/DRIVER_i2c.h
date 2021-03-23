#ifndef _DRIVER_I2C_H
#define _DRIVER_I2C_H

#include "MKL46Z4.h"
#include "HAL_i2c.h"
#include <stdlib.h>
#include <stdbool.h>

/*******************************************************************
@: Define I2C_Master for User
********************************************************************/
typedef struct
{
    I2C_Type * base;
    uint32_t baudRate_kbps;
}I2Cx_Master;

/*******************************************************************
@brief: Init I2C Master
@param1: I2C_Master for User
@return:  Init State
********************************************************************/
I2C_Status DRV_I2Cx_InitMaster(I2Cx_Master i2cMasterInit);

/*******************************************************************
@brief: Send 1 byte data
@param1: base of I2Cx (0 or 1)
@param2: 1 byte data
@return: None
********************************************************************/
void DRV_I2Cx_WriteData(I2C_Type * base,uint8_t data);

/*******************************************************************
@brief: Read 1 byte data
@param1: base of I2Cx (0 or 1)
@param2: 1 byte data
@return: None
********************************************************************/
uint8_t DRV_I2Cx_ReadData(I2C_Type * base);

/*******************************************************************
@brief: Start Condition of one Messenger
@param1: base of I2Cx (0 or 1)
@return: None
********************************************************************/
void DRV_I2C_Start(I2C_Type * base);

/*******************************************************************
@brief: Stop Condition of one Messenger
@param1: base of I2Cx (0 or 1)
@return: None
********************************************************************/
void DRV_I2Cx_Stop(I2C_Type * base);

/*******************************************************************
@brief: Send n byte data
@param1: base of I2Cx (0 or 1)
@param2: Adddresss of slave
@param3: buffer data
@param4: Size of block data (n byte)
@return: None
********************************************************************/
void DRV_I2Cx_MasterSendData(I2C_Type *base,uint8_t slaveAddress, uint8_t * bufData,uint32_t sizeData);

/*******************************************************************
@brief: Receive n byte data
@param1: base of I2Cx (0 or 1)
@param2: Adddresss of slave
@param3: buffer data
@param4: Size of block data (n byte)
@return: None
********************************************************************/
void DRV_I2Cx_MasterReceiveData(I2C_Type *base,uint8_t slaveAddress, uint8_t * bufData,uint32_t sizeData);
#endif /*_DRIVER_I2C_H*/