#ifndef __BOARD_H_
#define __BOARD_H_
#include "MKL46Z4.h"
#include "HAL_gpio.h"
#include "HAL_port.h"

/* Define for RED Led*/
#define PORT_RED_LED      PORTE
#define PIN_RED_LED       PIN_29
#define GPIO_RED_LED      GPIOE
#define RED_LED_ON        (HAL_GPIO_WritePin(GPIO_RED_LED,PIN_RED_LED,PIN_RESET))
#define RED_LED_OFF       (HAL_GPIO_WritePin(GPIO_RED_LED,PIN_RED_LED,PIN_SET))
#define RED_LED_TOGGLE    (DRV_GPIO_TogglePin(GPIO_RED_LED,PIN_RED_LED))

/* Define for GREEN LED*/
#define PORT_GREEN_LED    PORTD
#define PIN_GREEN_LED     PIN_5
#define GPIO_GREEN_LED    GPIOD
#define GREEN_LED_ON      (HAL_GPIO_WritePin(GPIO_GREEN_LED,PIN_GREEN_LED,PIN_RESET))
#define GREEN_LED_OFF     (HAL_GPIO_WritePin(GPIO_GREEN_LED,PIN_GREEN_LED,PIN_SET))
#define GREEN_LED_TOGGLE  (DRV_GPIO_TogglePin(GPIO_GREEN_LED,PIN_GREEN_LED))

/* Define for SW1*/
#define PORT_SW1          PORTC
#define PIN_SW1           PIN_3
#define GPIO_SW1          GPIOC
#define SW1_PRESSDOWN     (HAL_GPIO_ReadPin(GPIO_SW1,PIN_SW1)==PIN_RESET)

/* Define for SW2*/
#define PORT_SW2          PORTC
#define PIN_SW2           PIN_12
#define GPIO_SW2          GPIOC
#define SW2_PRESSDOWN     (HAL_GPIO_ReadPin(GPIO_SW2,PIN_SW2)==PIN_RESET)

/*Define for I2C0 */
#define I2C0_SELECT       (1U)
#define PORT_I2C0         PORTC
#define PIN_I2C0_SCL      PIN_8
#define PIN_I2C0_SDA      PIN_9

/*Define for I2C1 */
#define I2C1_SELECT       (0U)
#define PORT_I2C1         PORTC
#define PIN_I2C1_SCL      PIN_10
#define PIN_I2C1_SDA      PIN_11

/*Define for keyboard*/
#define PORT_KEYBOARD        PORTD
#define GPIO_KEYBOARD        GPIOD
#define PIN_KEYBOARD_2       PIN_4
#define PIN_KEYBOARD_3       PIN_5
#define PIN_KEYBOARD_1       PIN_6
#define PIN_KEYBOARD_4       PIN_7
#endif /*__BOARD_H_*/