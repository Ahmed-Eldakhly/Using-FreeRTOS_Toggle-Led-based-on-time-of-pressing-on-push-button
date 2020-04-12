/*************************************************
 * Module     : PushButton
 *
 * File name  : PushButton.c
 *
 * Created on : Oct 6, 2019
 *
 * Author     : Hesham Hafez & Ahmed El-Dakhly
 *************************************************/

/*************************************************
 *              Included libraries
 *************************************************/
#include "PushButton.h"

/********************************************************************************
 *              Functions Definition                                            *
 ********************************************************************************/
/********************************************************************************
 * Function Name:   PushButton_Init
 *
 * Description:     Initialize Push Button
 *
 * Inputs:          NULL
 *
 * Outputs:         NULL
 *
 * Return:          NULL
 *******************************************************************************/
void PushButton_Init(void)
{
    /*set Pins Of Push Button*/
    GPIO_SetPinDirection(GPIO_PORTF_DATA_BITS_R, GPIO_PIN4, INPUT, DIGITAL_ENABLE);


}

/*******************************************************************************
 * Function Name:   Buttons_getPressedButton
 *
 * Description:     Return value of pressed Bush Button
 *
 * Inputs:          NULL
 *
 * Outputs:         NULL
 *
 * Return:          pressed Push Button (uint8_t)
 *******************************************************************************/
uint8_t Buttons_getPressedButton(void)
{
    /*return value*/
    uint8_t ReturnVal=10;


    /*Loop to check if button is pressed to return its value*/
    if(GPIO_ReadPin(GPIO_PORTF_DATA_BITS_R , GPIO_PIN0) == 0)
    {
        ReturnVal = 2;
    }
    else if(GPIO_ReadPin(GPIO_PORTF_DATA_BITS_R , GPIO_PIN4) == 0)
    {
        ReturnVal = 1;
    }
    else
    {
        /*Do Nothing*/
    }
    return ReturnVal;
}
