/*
 * task.h
 *
 *  Created on: Nov 21, 2025
 *      Author: sammy
 */

#ifndef INC_TASK_H_
#define INC_TASK_H_

#include <stdio.h>
#include "cmsis_os.h"
#include "gpio.h"
#include "fonctions.h"
#include "Shell.h"

#define PERIOD_TOGGLE (100 / portTICK_PERIOD_MS) // Corresponds to 100ms.
#define DELAY_100MS (100 / portTICK_PERIOD_MS)
#define DELAY_1S (1000 / portTICK_PERIOD_MS) // Corresponds to 1000ms.


extern TaskHandle_t h_task_ToggleLED ;
extern int btn_flag ;
extern TaskHandle_t h_task_spam;
extern TaskHandle_t HandleTaskTake;
extern TaskHandle_t h_task_shell;
extern TaskHandle_t h_task_overflow;

void task_shell (void* unused);
void task_spam(void * unused);
void task_ToggleLED(void * unused);
void taskGive(void * unused);
void taskTake(void * unused);
void task_bug(void * pvParameters);
void task_stack_overflow(void *unused);

#endif /* INC_TASK_H_ */
