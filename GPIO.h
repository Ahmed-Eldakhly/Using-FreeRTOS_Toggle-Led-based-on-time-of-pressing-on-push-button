/*************************************************
 * Module     : GPIO Driver
 *
 * File name  : GPIO.h
 *
 * Created on : Oct 1, 2019
 *
 * Author     : Hesham Hafez & Ahmed El-Dakhly
 *************************************************/

#ifndef GPIO_H_
#define GPIO_H_

/*************************************************
 *              Included libraries
 *************************************************/
#include "tm4c123gh6pm.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define OUTPUT                          1u
#define INPUT                           0u

#define HIGH                            1u
#define LOW                             0u

#define PIN_AS_GPIO                     0u
#define PIN_AS_ALTERNATE                1u

#define DIGITAL_ENABLE                  0u
#define DIGITAL_DISABLE                 1u

/*GPIO Pins*/
#define GPIO_PIN0                       0u
#define GPIO_PIN1                       1u
#define GPIO_PIN2                       2u
#define GPIO_PIN3                       3u
#define GPIO_PIN4                       4u
#define GPIO_PIN5                       5u
#define GPIO_PIN6                       6u
#define GPIO_PIN7                       7u

/*Offsets*/
#define DATA_REGISTER_OFFSET          0xFFu
#define DIRECTION_OFFSET              0x100u
#define ALTERNATE_GPIO_SELECT_OFFSET  0x108u
#define CURRENT_8MA                   0x142u
#define OPENDRAIN_OFFSET              0x143u
#define PULLUP_OFFSET                 0x144u
#define PULLDOWN_OFFSET               0x145u
#define SLEW_RATE_OFFSET              0x146u
#define DIGITAL_OFFSET                0x147u
#define LOCK_OFFSET                   0x148u
#define COMMIT_REGISTER_OFFSET        0x149u


/************************************************
 *              Functions Deceleration
 ************************************************/

/*******************************************************************************
 * Function Name:   GPIO_SetPinDirection
 *
 * Description:     Set Direction of GPIO Pin
 *
 * Inputs:          pointer to Port Base (uint32_t)
 *                  Pin                  (uint8_t)
 *                  Direction            (uint8_t)
 *                  DigitalEnable        (uint8_t)
 *
 * Outputs:         NULL
 *
 * Return:          NULL
 *******************************************************************************/
void GPIO_SetPinDirection(volatile uint32_t * PortBase , uint8_t Pin , uint8_t Direction , uint8_t DigitalEnable);

/*******************************************************************************
 * Function Name:   Alternate_GPIO_Select
 *
 * Description:     Enable Alternative Function of Pin
 *
 * Inputs:          pointer to Port Base (uint32_t)
 *                  Pin                  (uint8_t)
 *
 * Outputs:         NULL
 *
 * Return:          NULL
 *******************************************************************************/
void Alternate_GPIO_Select(volatile uint32_t * PortBase , uint8_t Pin);

/*******************************************************************************
 * Function Name:   GPIO_WritePin
 *
 * Description:     write on output Pin
 *
 * Inputs:          pointer to Port Base (uint32_t)
 *                  Pin                  (uint8_t)
 *                  written Value        (uint8_t)
 *
 * Outputs:         NULL
 *
 * Return:          NULL
 *******************************************************************************/
void GPIO_WritePin(volatile uint32_t * PortBase , uint8_t Pin , uint32_t Value);

/*******************************************************************************
 * Function Name:   GPIO_ReadPin
 *
 * Description:     read from input Pin
 *
 * Inputs:          pointer to Port Base (uint32_t)
 *                  Pin                  (uint8_t)
 *
 * Outputs:         NULL
 *
 * Return:          uint8_t
 *******************************************************************************/
uint8_t GPIO_ReadPin(volatile uint32_t * PortBase , uint8_t Pin );

/*******************************************************************************
 * Function Name:   GPIO_UnlockPin
 *
 * Description:     Unlock Locked Pin
 *
 * Inputs:          pointer to Port Base (uint32_t)
 *                  Pin                  (uint8_t)
 *                  Unlock Value         (uint8_t)
 *
 * Outputs:         NULL
 *
 * Return:          NULL
 *******************************************************************************/
void GPIO_UnlockPin(volatile uint32_t * PortBase , uint8_t Pin , uint8_t CommitValue);




#endif /* GPIO_H_ */
