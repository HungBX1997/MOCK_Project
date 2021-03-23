#include "tea5767.h"
#include "lcd.h"
#include "DRIVER_i2c.h"

extern I2Cx_Master i2cMaster;
void setFrequency(float frequency,uint32_t statusMute) {
    /* High side injection*/
    unsigned int frequencyB = (unsigned int)(4 * (frequency * 1000000 + 225000) / 32768);
    uint8_t data_arr[5];
    data_arr[0] = (frequencyB >> 8);
    if( statusMute )
    {
        data_arr[0] = (frequencyB >> 8)|TEA5767_MUTE_MASK;
    }
    data_arr[1] = frequencyB & 0XFF;
    data_arr[2] = 0xB0;
    data_arr[3] = 0x10;
    data_arr[4] = 0x00;
#if I2C0_SELECT
    DRV_I2Cx_MasterSendData(i2cMaster.base,ADD_TEA5767,data_arr,5);
#endif
#if I2C1_SELECT
    DRV_I2Cx_MasterSendData(i2cMaster.base,ADD_TEA5767,data_arr,5);
#endif
}

void scanFrequency(uint8_t scanDirection)
{
    uint8_t r_buffer[5] = { 0, 0, 0, 0, 0 };
    uint8_t w_buffer[5] = { 0, 0, 0, 0, 0 };
    
    
    // Make sure I2C is initialised
    // First we need to get the current PLL word to know where to start from
    DRV_I2Cx_MasterReceiveData(i2cMaster.base,ADD_TEA5767,r_buffer,5);
    
    // Set the PLL value again and append the search enable bu
    w_buffer[0] = TEA5767_SEARCH_MASK |          // Search mode enabled
                (r_buffer[0] & 0x3F);                 // Upper PLL bits
    w_buffer[1] = r_buffer[1];                          // Lower PLL bits
    w_buffer[2] = TEA5767_SEARCH_STOP_MID_MASK | // Mid level ADC for search steps
                TEA5767_HI_INJECTION_MASK;                 // HLSI (must be 1 for PLL)
    w_buffer[3] = TEA5767_XTAL_MASK;                 // Must be 1 for 32.768kHz crystal
    w_buffer[4] = 0x00;
    
    // Set the scan direction bit to 1 (scan up) if scanDirection is non-zero
    if (scanDirection) w_buffer[2] |= TEA5767_SEARCH_UP_MASK;
    
    // Send data over I2C
    DRV_I2Cx_MasterSendData(i2cMaster.base,ADD_TEA5767,w_buffer,5);
    DRV_Delay(40);
}