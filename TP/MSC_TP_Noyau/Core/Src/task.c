/*
 * task.c
 *
 *  Created on: Nov 21, 2025
 *      Author: sammy
 */

#include "task.h"

TaskHandle_t h_task_ToggleLED;
int btn_flag;

void task_ToggleLED(void * unused)
{
	for (;;)
	{
/*
		HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
		printf("LED toggled \n\r");
		vTaskDelay(PERIOD_TOGGLE);
*/
	}
}


//SemaphoreHandle_t sem_task;
//sem_task = xSemaphoreCreateBinary();
TaskHandle_t HandleTaskTake;

void taskGive(void * unused)
{
	uint32_t taskGive_delay = DELAY_100MS;
	for(;;)
	{
		printf("TaskGive: I'm going to give a semaphore \r\n");
		//xSemaphoreGive(sem_task);
		xTaskNotifyGive(HandleTaskTake);
		printf("TaskGive: I gave semaphore \r\n");
		vTaskDelay(taskGive_delay);
		taskGive_delay+=DELAY_100MS;
	}
}

void taskTake(void * unused)
{
	for(;;)
	{
		printf("TaskTake: I'm going to take a semaphore \r\n");
		uint32_t status = ulTaskNotifyTake(pdTRUE, DELAY_1S);
		//if (xSemaphoreTake(sem_task, pdMS_TO_TICKS(1000)) == pdTRUE)
		if (status > 0)
		{
			printf("TaskTake: I took semaphore \r\n");
		}
		else
		{
			printf("TaskTake ERROR: semaphore NOT received within 1s!\r\n");
			printf("TaskTake: Performing software reset...\r\n");
			NVIC_SystemReset();
		}
	}
}


void task_bug(void * pvParameters)
{
	int delay = (int) pvParameters;
	for(;;)
	{
		printf("Je suis %s et je m'endors pour \
		%d ticks\r\n", pcTaskGetName(NULL), delay);
		vTaskDelay(delay);
	}
}
