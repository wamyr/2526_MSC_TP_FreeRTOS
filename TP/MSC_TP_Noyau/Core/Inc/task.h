/*
 * task.h
 *
 *  Created on: Nov 21, 2025
 *      Author: sammy
 */

#ifndef INC_TASK_H_
#define INC_TASK_H_

#include <main.h>
#include <stdio.h>
#include "cmsis_os.h"
#include "gpio.h"


#define PERIOD_TOGGLE (100 / portTICK_PERIOD_MS) // Corresponds to 100ms.
#define DELAY_100MS (100 / portTICK_PERIOD_MS)
#define DELAY_1S (1000 / portTICK_PERIOD_MS) // Corresponds to 1000ms.


extern TaskHandle_t h_task_ToggleLED ;
extern int btn_flag ;
//extern SemaphoreHandle_t sem_task;
extern TaskHandle_t HandleTaskTake;


void task_ToggleLED(void * unused);
void taskGive(void * unused);
void taskTake(void * unused);
void task_bug(void * pvParameters);

#endif /* INC_TASK_H_ */
