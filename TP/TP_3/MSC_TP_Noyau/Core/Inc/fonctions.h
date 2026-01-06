/*
 * fonctions.h
 *
 *  Created on: Nov 21, 2025
 *      Author: sammy
 */

#ifndef INC_FONCTIONS_H_
#define INC_FONCTIONS_H_

#include <stdlib.h>
#include "gpio.h"
#include "task.h"
#include "usart.h"

#define FIVE_SEC 5000

extern TickType_t Period_Toggle;
extern TickType_t Period_Delay_msg;
extern char* message;
extern int number_msg;

int ToggleLED(int argc, char ** argv);
int fonction(int argc, char ** argv);
int addition(int argc, char ** argv);
int spam(int argc, char ** argv);


#endif /* INC_FONCTIONS_H_ */
