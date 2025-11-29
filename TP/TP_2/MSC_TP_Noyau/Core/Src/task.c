/*
 * task.c
 *
 *  Created on: Nov 21, 2025
 *      Author: sammy
 */

#include "task.h"

TaskHandle_t h_task_shell;

void task_shell (void* unused)
{
	shell_init();
	shell_add('f', fonction, "Une fonction inutile");
	shell_add('a', addition, "Ma super addition");
	shell_add('l', ToggleLED, "Une fonction qui prend en paramètre Period_toggle compris entre 0 et 4.9s.");
	shell_add('s', spam, "spam avec message nombre frequence");
	shell_run();

	// une tâche ne doit JAMAIS retourner ou alors utiliser vtaskdelete
	// ici dans tout les cas c'est une boucle infini donc ne retournera rien.
}



int btn_flag;
TaskHandle_t h_task_ToggleLED;


void task_ToggleLED(void * unused)
{
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, RESET);
	vTaskSuspend(NULL);
	for (;;){
	HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
	vTaskDelay(Period_Toggle);
	}
}


TaskHandle_t h_task_spam;

void task_spam(void * unused)
{
	vTaskSuspend(NULL);
	for (;;){
	for(int i = 0; i < number_msg; i++){
		printf("%s \r\n", message);
		vTaskDelay(Period_Delay_msg);
	}
	vTaskResume(h_task_shell); //without this line the shell command line doesn't display proprely
	vTaskSuspend(NULL);
	}
}


//SemaphoreHandle_t sem_task;
//sem_task = xSemaphoreCreateBinary();
TaskHandle_t HandleTaskTake;

void taskGive(void * unused)
{
	uint32_t taskGive_delay = DELAY_100MS;
	uint32_t CurrentTime;
	for(;;)
	{
		printf("TaskGive: I'm going to give a semaphore \r\n");
		//xSemaphoreGive(sem_task);
		xTaskNotifyGive(HandleTaskTake);
		printf("TaskGive: I gave semaphore \r\n");

		CurrentTime= HAL_GetTick();
		if (xQueueSend(TaskGT_queue, &CurrentTime, 0) != pdPASS)
			printf("Queue full !\r\n");

		vTaskDelay(taskGive_delay);
		taskGive_delay+=DELAY_100MS;
	}
}

void taskTake(void * unused)
{
	uint32_t ReceivedTick;
	for(;;)
	{
		printf("TaskTake: I'm going to take a semaphore \r\n");
		uint32_t status = ulTaskNotifyTake(pdTRUE, DELAY_1S);
		if (xQueueReceive(TaskGT_queue, &ReceivedTick, portMAX_DELAY) == pdTRUE)
		{
			printf("Current tick received : %lu\r\n", ReceivedTick);
		}
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
		if (xSemaphoreTake(Task_bug_mutex, portMAX_DELAY) == pdTRUE)
		{
			printf("Je suis %s et je m'endors pour \
			%d ticks\r\n", pcTaskGetName(NULL), delay);
			xSemaphoreGive(Task_bug_mutex);
		}
		else
		{
			printf("%s ERROR: semaphore mutex NOT received within %lu !\r\n", pcTaskGetName(NULL), portMAX_DELAY);
			printf("Performing software reset...\r\n");
			NVIC_SystemReset();
		}
		vTaskDelay(delay);
	}
}

