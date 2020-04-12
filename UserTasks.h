/*****************************************************************************
 * Module 	  : FreeRTOS User Story3 Tasks Prototypes
 *
 * File name  : UserTasks.h
 *
 * Created on : Oct 6, 2019
 *
 * Author     : Ahmed El-Dakhly & Hesham Hafez
 *************************************************/

#ifndef USERTASKS_H_
#define USERTASKS_H_

/*******************************************************************************
 *                       	Included Libraries                                 *
 *******************************************************************************/
#include "FreeRTOS.h"
#include "task.h"
#include "Macro.h"
#include "PushButton.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
extern TaskHandle_t  InitTask_Flag;

/*******************************************************************************
 *                      Functions Prototypes        	                       *
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
void init_Task(void * a_Task_ptr);

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
void All_Hardware_Init_Task(void * a_Task_ptr);

/*******************************************************************************
 * Function Name:	PushButton_Task
 *
 * Description: 	Push Button & App Task
 *
 * Inputs:			pointer to void
 *
 * Outputs:			NULL
 *
 * Return:			NULL
 *******************************************************************************/
void PushButton_Task(void * a_Task_ptr);



#endif /* USERTASKS_H_ */
