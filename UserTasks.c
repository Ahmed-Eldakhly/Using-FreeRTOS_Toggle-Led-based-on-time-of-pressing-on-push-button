/*****************************************************************************
 * Module     : FreeRTOS User Story3 Tasks Prototypes
 *
 * File name  : UserTasks.h
 *
 * Created on : Oct 6, 2019
 *
 * Author     : Ahmed El-Dakhly & Hesham Hafez
 *************************************************/

/*******************************************************************************
 *                       	Included Libraries                                 *
 *******************************************************************************/
#include "UserTasks.h"

/*******************************************************************************
 *                                 Macros                                      *
 *******************************************************************************/
#define IDLE                  0
#define PRESSED_LESS_2        1
#define PRESSED_LESS_4        2
#define PRESSED_MORE_4        3

/*******************************************************************************
 *                           Global Variables                    		       *
 *******************************************************************************/
TaskHandle_t  InitTask_Flag = NULL;
static TaskHandle_t  AllHardwareInit_Flag = NULL;

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*******************************************************************************
 * Function Name:	init_Task
 *
 * Description: 	Create all tasks in the system
 *
 * Inputs:			pointer to void
 *
 * Outputs:			NULL
 *
 * Return:			NULL
 *******************************************************************************/
void init_Task(void * a_Task_ptr)
{
    /*create Hardware Initialization Task*/
    xTaskCreate(All_Hardware_Init_Task  , "InitTasks" , configMINIMAL_STACK_SIZE ,
                NULL , (4 | portPRIVILEGE_BIT) , &AllHardwareInit_Flag);

    /*create App Task*/
    xTaskCreate(PushButton_Task  , "PushButton_Task" , configMINIMAL_STACK_SIZE ,
                NULL , (2 | portPRIVILEGE_BIT) , NULL);

    /*suspend initialization task*/
    vTaskSuspend( InitTask_Flag);
}

/*******************************************************************************
 * Function Name:	All_Hardware_Init_Task
 *
 * Description: 	Initialize LCD & KeyPad
 *
 * Inputs:			pointer to void
 *
 * Outputs:			NULL
 *
 * Return:			NULL
 *******************************************************************************/
void All_Hardware_Init_Task(void * a_Task_ptr)
{
    /*Push Button initialization*/
    PushButton_Init();

    /*GPIO Init*/
    GPIO_SetPinDirection(GPIO_PORTF_DATA_BITS_R, GPIO_PIN2, OUTPUT, DIGITAL_ENABLE);

    /*suspend All Hardware Initialization Task task*/
    vTaskSuspend( AllHardwareInit_Flag);
}

/*******************************************************************************
 * Function Name:   PushButton_Task
 *
 * Description:     Push Button & App Task
 *
 * Inputs:          pointer to void
 *
 * Outputs:         NULL
 *
 * Return:          NULL
 *******************************************************************************/
void PushButton_Task(void * a_Task_ptr)
{
    /*count Pressed Time*/
    uint8_t Counter = 0;

    /*counter to toggle led in specific time*/
    uint8_t ToggleCounter = 0;

    /*Push Button State*/
    uint8_t ButtonState = IDLE;


    while(1)
    {
        /*state machine for Push Button */
        switch(ButtonState)
        {
        case IDLE:
            /*reset time counter*/
            Counter = 0;
            /*Push Button Pressed */
            if((GPIO_ReadPin(GPIO_PORTF_DATA_BITS_R, GPIO_PIN4)) == 0)
            {
                ButtonState = PRESSED_LESS_2;
            }
            /*Periodic time of task*/
            vTaskDelay(100);
            break;
        case PRESSED_LESS_2:
            /*Push Button is Pressed for time less than 2 seconds*/
            if(((GPIO_ReadPin(GPIO_PORTF_DATA_BITS_R, GPIO_PIN4)) == 0) && Counter < 20)
            {
                Counter++;
            }
            /*Button is Pressed for time more than 2 seconds*/
            else if((GPIO_ReadPin(GPIO_PORTF_DATA_BITS_R, GPIO_PIN4)) == 0)
            {
                ButtonState = PRESSED_LESS_4;
            }
            /* Button is released*/
            else
            {
                /*LED Off*/
                GPIO_WritePin(GPIO_PORTF_DATA_BITS_R, GPIO_PIN2, LOW);
                ButtonState = IDLE;
            }
            /*Periodic time of task*/
            vTaskDelay(100);
            break;
        case PRESSED_LESS_4:
            /*Push Button is Pressed for time more than 2 seconds and less than 4 seconds*/
            if(((GPIO_ReadPin(GPIO_PORTF_DATA_BITS_R, GPIO_PIN4)) == 0) && Counter < 40)
            {
                Counter++;
            }
            /*Button is Pressed for time more than 4 seconds*/
            else  if((GPIO_ReadPin(GPIO_PORTF_DATA_BITS_R, GPIO_PIN4)) == 0)
            {
                ButtonState = PRESSED_MORE_4;
            }
            /* Button is released in time more than 2 seconds and less than 4 seconds*/
            else
            {
                /*while Button Don't be pressed again*/
                while(GPIO_ReadPin(GPIO_PORTF_DATA_BITS_R, GPIO_PIN4))
                {
                    /*Toggle Led every 400 ms*/
                    if(ToggleCounter<4)
                    {
                        GPIO_WritePin(GPIO_PORTF_DATA_BITS_R, GPIO_PIN2, HIGH);
                        ToggleCounter++;
                    }
                    else if(ToggleCounter<8)
                    {
                        GPIO_WritePin(GPIO_PORTF_DATA_BITS_R, GPIO_PIN2, LOW);
                        ToggleCounter++;
                    }
                    else
                    {
                        ToggleCounter = 0;
                    }
                    /*Periodic time of task*/
                    vTaskDelay(100);
                }
                ButtonState = IDLE;
            }
            /*Periodic time of task*/
            vTaskDelay(100);
            break;
        case PRESSED_MORE_4:
            /*reset Toggle Led counter*/
            ToggleCounter = 0;
            /*Check if led is Not Released*/
            while((GPIO_ReadPin(GPIO_PORTF_DATA_BITS_R, GPIO_PIN4)) == 0)
            {
                /*Periodic time of task*/
                vTaskDelay(100);
            }
            /*Check if led is Released*/
            while(GPIO_ReadPin(GPIO_PORTF_DATA_BITS_R, GPIO_PIN4))
            {
                /*Toggle Led every 1 ms*/
                if(ToggleCounter<1)
                {
                    GPIO_WritePin(GPIO_PORTF_DATA_BITS_R, GPIO_PIN2, HIGH);
                    ToggleCounter++;
                }
                else if(ToggleCounter<2)
                {
                    GPIO_WritePin(GPIO_PORTF_DATA_BITS_R, GPIO_PIN2, LOW);
                    ToggleCounter++;
                }
                else
                {
                    ToggleCounter = 0;
                }
                /*Periodic time of task*/
                vTaskDelay(100);
            }
            ButtonState = IDLE;
            break;
        }
    }
}

