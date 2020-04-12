



#include "UserTasks.h"


void main(void)
{
	xTaskCreate(init_Task  , "Init_Task" , configMINIMAL_STACK_SIZE ,
			NULL , (3 | portPRIVILEGE_BIT) , &InitTask_Flag);
	vTaskStartScheduler();
	while(1)
	{

	}
}

