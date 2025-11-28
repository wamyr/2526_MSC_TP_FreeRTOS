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

int fonction(int argc, char ** argv) // char ** : pointeur de pointeur ou tableau de tableau
{
	printf("Nombre d'argument : %d \r\n", argc);

	for (int i =0 ; i<argc; i++)
	{
		printf("argv[%d] = %s \r\n", i, argv[i]);
	}

	return 0;
}

int addition(int argc, char ** argv) //format classique
{
	if (argc != 3)
	{
		printf("expected two arguments \r\n"); // ATTENTION SI PAS DE \n  PRINTF STOCKER DANS TABLEAU CHACHE DONC QUAND ON APPEllERA PRINTF, MEME SI ERREUR CORRIGE, CA RENVOIT CE QU IL Y A DANS CE TABLEAU, DONC CA PEUT FAIRE CROIRE QUE C EST PAS CORRIGE ALORS QUE SI
		return -1; //arrête la fonction et -1 correspond traditionnellement à une erreur.
	}
	int a = atoi(argv[1]);
	int b = atoi(argv[2]);
	int c = a + b ;

	printf("%d + %d = %d \r\n", a, b,c);


	return 0;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{


	if(GPIO_Pin == B1_Pin){
		//HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
		btn_flag = 1;
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart -> Instance == USART2)
	{
		//Caractère reçu : Donner le sémaphore pour débloquer task_shell
		shell_uart_rx_callback();
	}

}
