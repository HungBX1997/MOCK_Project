#include "DRIVER_i2c.h"


/* DRV - Init Master for I2Cx*/
I2C_Status DRV_I2Cx_InitMaster(I2Cx_Master  i2cMasterInit)
{
    HAL_I2Cx_InitMaster(i2cMasterInit.base,i2cMasterInit.baudRate_kbps);
    return I2C_Success;
}

/* DRV - Send 1 byte data*/
void DRV_I2Cx_WriteData(I2C_Type * base,uint8_t data)
{
    HAL_I2Cx_WriteData(base,data);
}

/* DRV - Send 1 byte data*/
uint8_t DRV_I2Cx_ReadData(I2C_Type * base)
{
    return HAL_I2Cx_ReadData(base);
}

/* DRV - Init Start Condition*/
void DRV_I2C_Start(I2C_Type * base)
{
    HAL_I2Cx_Start(base);
}

/* DRV - Init Stop Condition*/
void DRV_I2Cx_Stop(I2C_Type * base)
{
    HAL_I2Cx_Stop(base);
}

/* DRV - Send n byte data*/
void DRV_I2Cx_MasterSendData(I2C_Type *base,uint8_t slaveAddress, uint8_t * bufData,uint32_t sizeData)
{
    HAL_I2Cx_MasterSendData(base,slaveAddress,bufData,sizeData);
}

/* DRV - Receive n byte data*/
void DRV_I2Cx_MasterReceiveData(I2C_Type *base,uint8_t slaveAddress, uint8_t * bufData,uint32_t sizeData)
{
    HAL_I2Cx_MasterReceiveData(base,slaveAddress,bufData,sizeData);
}