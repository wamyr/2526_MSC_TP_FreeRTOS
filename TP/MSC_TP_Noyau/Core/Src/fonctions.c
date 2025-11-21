/*
 * fonctions.c
 *
 *  Created on: Nov 21, 2025
 *      Author: sammy
 */

#include "fonctions.h"



void ToggleLED()
{
	HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
	HAL_Delay(200);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{


	if(GPIO_Pin == B1_Pin){
		//HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
		btn_flag = 1;
	}

}
