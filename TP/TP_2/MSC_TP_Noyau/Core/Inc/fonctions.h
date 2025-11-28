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


void ToggleLED();
int fonction(int argc, char ** argv);
int addition(int argc, char ** argv);

#endif /* INC_FONCTIONS_H_ */
