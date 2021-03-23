#ifndef __FSL_HAL_PORT_H__
#define __FSL_HAL_PORT_H__

#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include "MKL46Z4.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*Define number PIN for each port*/
typedef enum {
    PIN_0 =0,
    PIN_1 =1,
    PIN_2 =2,
    PIN_3,
    PIN_4,
    PIN_5,
    PIN_6,
    PIN_7,
    PIN_8,
    PIN_9,
    PIN_10,
    PIN_11,
    PIN_12,
    PIN_13,
    PIN_14,
    PIN_15,
    PIN_16,
    PIN_17,
    PIN_18,
    PIN_19,
    PIN_20,
    PIN_21,
    PIN_22,
    PIN_23,
    PIN_24,
    PIN_25,
    PIN_26,
    PIN_27,
    PIN_28,
    PIN_29, 
    PIN_30,
    PIN_31
} PIN_name;

/*! @brief Internal resistor pull feature selection*/
typedef enum {
    PullDown = 0U,  
    PullUp   = 1U  
} PORT_pull;

/*! @brief Slew rate selection*/
typedef enum {
    FastSlewRate = 0U,  
    SlowSlewRate = 1U  
} PORT_Rate;

/*! @brief Configures the drive strength.*/
typedef enum  {
    LowDriveStrength  = 0U, 
    HighDriveStrength = 1U  
} PORT_drive_strength;

/*! @brief Pin mux selection*/
typedef enum {
    PinDisabled = 0U,
    MuxAsGpio   = 1U,
    MuxAlt2     = 2U,
    MuxAlt3     = 3U,
    MuxAlt4     = 4U,
    MuxAlt5     = 5U,
    MuxAlt6     = 6U,
    MuxAlt7     = 7U
} PORT_MUX;

/*! @brief Configures the interrupt generation condition.*/
typedef enum {
    IntDisabled    = 0x0U,
    DmaRisingEdge  = 0x1U,
    DmaFallingEdge = 0x2U,
    DmaEitherEdge  = 0x3U,
    IntLogicZero   = 0x8U,
    IntRisingEdge  = 0x9U,
    IntFallingEdge = 0xAU,
    IntEitherEdge  = 0xBU,
    IntLogicOne    = 0xCU
} PORT_Interrupt;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Configuration
 * @{
 */
void EnableClockPort(PORT_Type *port_base);
  
/*!
 * @brief Selects the internal resistor as pull-down or pull-up.
 *
 * Pull configuration is valid in all digital pin muxing modes.
 *
 * @param base  port base pointer.
 * @param pin       port pin number
 * @param pullSelect  internal resistor pull feature selection
 *        - PullDown: internal pull-down resistor is enabled.
 *        - PullUp  : internal pull-up resistor is enabled.
 */
 void HAL_PORT_SetPullMode(PORT_Type * base,
                                        PIN_name pin,
                                        PORT_pull pullSelect);


/*!
 * @brief Enables or disables the internal pull resistor.
 *
 * @param base  port base pointer
 * @param pin       port pin number
 * @param isPullEnabled  internal pull resistor enable or disable
 *        - true : internal pull resistor is enabled.
 *        - false: internal pull resistor is disabled.
 */
 void HAL_PORT_PullEnable(PORT_Type * base,
                                       PIN_name pin,
                                       bool isPullEnabled);

/*!
 * @brief Configures the pin muxing.
 *
 * @param base  port base pointer
 * @param pin  port pin number
 * @param mux  pin muxing slot selection
 *        - PinDisabled: Pin disabled.
 *        - MuxAsGpio  : Set as GPIO.
 *        - others          : chip-specific.
 */
 void HAL_PORT_SetMuxMode(PORT_Type * base,
                                       PIN_name pin,
                                       PORT_MUX mux);


/*!
 * @brief Configures the low half of the pin control register for the same settings.
 *        This function operates pin 0 -15 of one specific port.
 *
 * @param base  port base pointer
 * @param lowPinSelect  update corresponding pin control register or not. For a specific bit:
 *        - 0: corresponding low half of pin control register won't be updated according to configuration.
 *        - 1: corresponding low half of pin control register will be updated according to configuration.
 * @param config  value  is written to a low half port control register bits[15:0].
 */
void HAL_PORT_SetLowGlobalPinCtrl(PORT_Type * base, uint16_t lowPinSelect, uint16_t config);

/*!
 * @brief Configures the high half of the pin control register for the same settings.
 *        This function operates pin 16 -31 of one specific port.
 *
 * @param base  port base pointer
 * @param highPinSelect  update corresponding pin control register or not. For a specific bit:
 *        - 0: corresponding high half of pin control register won't be updated according to configuration.
 *        - 1: corresponding high half of pin control register will be updated according to configuration.
 * @param config  value is  written to a high half port control register bits[15:0].
 */
void HAL_PORT_SetHighGlobalPinCtrl(PORT_Type * base, uint16_t highPinSelect, uint16_t config);

/*@}*/

/*!
 * @name Interrupt
 * @{
 */

/*!
 * @brief Configures the port pin interrupt/DMA request.
 *
 * @param base  port base pointer.
 * @param pin  port pin number
 * @param intConfig  interrupt configuration
 *        - IntDisabled   : Interrupt/DMA request disabled.
 *        - DmaRisingEdge : DMA request on rising edge.
 *        - DmaFallingEdge: DMA request on falling edge.
 *        - DmaEitherEdge : DMA request on either edge.
 *        - IntLogicZero  : Interrupt when logic zero.
 *        - IntRisingEdge : Interrupt on rising edge.
 *        - IntFallingEdge: Interrupt on falling edge.
 *        - IntEitherEdge : Interrupt on either edge.
 *        - IntLogicOne   : Interrupt when logic one.
 */
 void HAL_PORT_SetPinIntMode(PORT_Type * base,
                                          PIN_name pin,
                                          PORT_Interrupt intConfig);


/*!
 * @brief Gets the current port pin interrupt/DMA request configuration.
 *
 * @param base  port base pointer
 * @param pin  port pin number
 * @return  interrupt configuration
 *        - IntDisabled   : Interrupt/DMA request disabled.
 *        - DmaRisingEdge : DMA request on rising edge.
 *        - DmaFallingEdge: DMA request on falling edge.
 *        - DmaEitherEdge : DMA request on either edge.
 *        - IntLogicZero  : Interrupt when logic zero.
 *        - IntRisingEdge : Interrupt on rising edge.
 *        - IntFallingEdge: Interrupt on falling edge.
 *        - IntEitherEdge : Interrupt on either edge.
 *        - IntLogicOne   : Interrupt when logic one.
 */
 PORT_Interrupt HAL_PORT_GetPinIntMode(PORT_Type * base, PIN_name pin);


/*!
 * @brief Reads the individual pin-interrupt status flag.
 *
 * If a pin is configured to generate the DMA request,  the corresponding flag
 * is cleared automatically at the completion of the requested DMA transfer.
 * Otherwise, the flag remains set until a logic one is written to that flag.
 * If configured for a level sensitive interrupt that remains asserted, the flag
 * is set again immediately.
 *
 * @param base  port base pointer
 * @param pin  port pin number
 * @return current pin interrupt status flag
 *         - 0: interrupt is not detected.
 *         - 1: interrupt is detected.
 */
 bool HAL_PORT_IsPinIntPending(PORT_Type * base, PIN_name pin);


/*!
 * @brief Clears the individual pin-interrupt status flag.
 *
 * @param base  port base pointer
 * @param pin  port pin number
 */
 void HAL_PORT_ClearPinIntFlag(PORT_Type * base, PIN_name pin);

/*!
 * @brief Reads the entire port interrupt status flag.
 *
 * @param base  port base pointer
 * @return all 32 pin interrupt status flags. For specific bit:
 *         - 0: interrupt is not detected.
 *         - 1: interrupt is detected.
 */
 uint32_t HAL_PORT_GetPortIntFlag(PORT_Type * base,PIN_name pin);


/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* __FSL_HAL_PORT_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/

