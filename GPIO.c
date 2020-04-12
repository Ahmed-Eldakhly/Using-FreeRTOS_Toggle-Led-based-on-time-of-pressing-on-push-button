/*************************************************
 * Module     : GPIO Driver
 *
 * File name  : GPIO.c
 *
 * Created on : Oct 1, 2019
 *
 * Author     : Hesham Hafez & Ahmed El-Dakhly
 *************************************************/

/*************************************************
 *              Included libraries
 *************************************************/
#include "GPIO.h"
#include "Macro.h"

/********************************************************************************
 *              Functions Definition                                            *
 ********************************************************************************/
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
void GPIO_SetPinDirection(volatile uint32_t * PortBase , uint8_t Pin , uint8_t Direction , uint8_t DigitalEnable)
{
    /*set bit of pin number*/
    uint32_t Value = (1<<Pin);

    /*Open GPIO Port Clock*/
    if(PortBase == GPIO_PORTA_DATA_BITS_R)
    {
        SET_BIT(SYSCTL_RCGCGPIO_R , GPIO_PIN0);
        while(!GET_BIT(SYSCTL_PRGPIO_R , GPIO_PIN0));
        *(PortBase + CURRENT_8MA ) |= Value;
    }
    else if(PortBase==GPIO_PORTB_DATA_BITS_R)
    {
        SET_BIT(SYSCTL_RCGCGPIO_R , GPIO_PIN1);
        while(!GET_BIT(SYSCTL_PRGPIO_R , GPIO_PIN1));
        *(PortBase + CURRENT_8MA ) |= Value;
    }
    else if(PortBase==GPIO_PORTC_DATA_BITS_R)
    {
        SET_BIT(SYSCTL_RCGCGPIO_R , GPIO_PIN2);
        while(!GET_BIT(SYSCTL_PRGPIO_R , GPIO_PIN2));
        *(PortBase + CURRENT_8MA ) |= Value;
    }
    else if(PortBase==GPIO_PORTD_DATA_BITS_R)
    {
        SET_BIT(SYSCTL_RCGCGPIO_R , GPIO_PIN3);
        while(!GET_BIT(SYSCTL_PRGPIO_R , GPIO_PIN3));
        *(PortBase + CURRENT_8MA ) |= Value;
    }
    else if(PortBase==GPIO_PORTE_DATA_BITS_R)
    {
        SET_BIT(SYSCTL_RCGCGPIO_R , GPIO_PIN4);
        while(!GET_BIT(SYSCTL_PRGPIO_R , GPIO_PIN4));
        *(PortBase + CURRENT_8MA ) |= Value;
    }
    else if(PortBase==GPIO_PORTF_DATA_BITS_R)
    {
        SET_BIT(SYSCTL_RCGCGPIO_R , GPIO_PIN5);
        while(!GET_BIT(SYSCTL_PRGPIO_R , GPIO_PIN5));
        *(PortBase + CURRENT_8MA ) |= Value;
    }
    else
    {
        /*Do nothing*/
    }

    /*Set Pin Direction*/
    if(Direction == OUTPUT)
    {
        *(PortBase + DIRECTION_OFFSET ) |= Value;
    }
    else if(Direction == INPUT)
    {
        *(PortBase + DIRECTION_OFFSET ) &= ~Value;
    }
    else
    {
        /*Do nothing*/
    }

    /*Determine Digital Enable of Pin*/
    if(DigitalEnable == DIGITAL_ENABLE)
    {
        *(PortBase + DIGITAL_OFFSET ) |= Value;
    }
    else if(DigitalEnable == DIGITAL_DISABLE)
    {
        *(PortBase + DIGITAL_OFFSET ) &= ~Value;
    }
    else
    {
        /*Do nothing*/
    }

    /*select Pin as GPIO*/
    ( *(PortBase + ALTERNATE_GPIO_SELECT_OFFSET ) ) &= ~Value;

    /*Enable Pull Up resistor on Pin */
    ( *(PortBase + PULLUP_OFFSET ) ) |= Value;

    /*Disable Pull Down resistor on Pin */
    ( *(PortBase + PULLDOWN_OFFSET ) ) &= ~Value;

    /*Disable Open Drain on Pin */
    ( *(PortBase + OPENDRAIN_OFFSET ) ) &= ~Value;

    /*Disable Slew Rate on Pin */
    ( *(PortBase + SLEW_RATE_OFFSET ) ) &= ~Value;

}

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
void Alternate_GPIO_Select(volatile uint32_t * PortBase , uint8_t Pin)
{
    /*set bit of pin number*/
    uint32_t Value = (00000001<<Pin);

    /*Open GPIO Port Clock*/
    if(PortBase == GPIO_PORTA_DATA_BITS_R)
    {
        SET_BIT(SYSCTL_RCGCGPIO_R , GPIO_PIN0);
        while(!GET_BIT(SYSCTL_PRGPIO_R , GPIO_PIN0));
    }
    else if(PortBase==GPIO_PORTB_DATA_BITS_R)
    {
        SET_BIT(SYSCTL_RCGCGPIO_R , GPIO_PIN1);
        while(!GET_BIT(SYSCTL_PRGPIO_R , GPIO_PIN1));
    }
    else if(PortBase==GPIO_PORTC_DATA_BITS_R)
    {
        SET_BIT(SYSCTL_RCGCGPIO_R , GPIO_PIN2);
        while(!GET_BIT(SYSCTL_PRGPIO_R , GPIO_PIN2));
    }
    else if(PortBase==GPIO_PORTD_DATA_BITS_R)
    {
        SET_BIT(SYSCTL_RCGCGPIO_R , GPIO_PIN3);
        while(!GET_BIT(SYSCTL_PRGPIO_R , GPIO_PIN3));
    }
    else if(PortBase==GPIO_PORTE_DATA_BITS_R)
    {
        SET_BIT(SYSCTL_RCGCGPIO_R , GPIO_PIN4);
        while(!GET_BIT(SYSCTL_PRGPIO_R , GPIO_PIN4));
    }
    else if(PortBase==GPIO_PORTF_DATA_BITS_R)
    {
        SET_BIT(SYSCTL_RCGCGPIO_R , GPIO_PIN5);
        while(!GET_BIT(SYSCTL_PRGPIO_R , GPIO_PIN5));
    }
    else
    {
        /*Do nothing*/
    }

    /*select Pin as Alternate*/
    ( *(PortBase + ALTERNATE_GPIO_SELECT_OFFSET) ) |= Value;
}

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
void GPIO_WritePin(volatile uint32_t * PortBase , uint8_t Pin , uint32_t Value)
{
    if(Value == HIGH)
    {
       ( *(PortBase + DATA_REGISTER_OFFSET ) ) |= (1<<Pin);
    }
    else if(Value == LOW)
    {
        ( *(PortBase + DATA_REGISTER_OFFSET ) ) &= (~(1<<Pin));
    }
    else
    {
        /*Do Nothing*/
    }
}

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
uint8_t GPIO_ReadPin(volatile uint32_t * PortBase , uint8_t Pin )
{
    uint32_t Value ;
    Value = ((*(PortBase + DATA_REGISTER_OFFSET ))>>Pin) & 0x01;
    return Value;
}

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
void GPIO_UnlockPin(volatile uint32_t * PortBase , uint8_t Pin , uint8_t CommitValue )
{
    /*unlock Pin*/
    ( *(PortBase + LOCK_OFFSET) ) = 0x4C4F434B;

    /*Ditermine Pin Behaviour*/
    ( *(PortBase + COMMIT_REGISTER_OFFSET) ) |= (CommitValue << Pin);

    /*Lock Pin Again*/
   ( *(PortBase + LOCK_OFFSET) ) = 0x00000000;

}
