/*
 * fonctions.c
 *
 *  Created on: Nov 21, 2025
 *      Author: sammy
 */

#include "fonctions.h"

TickType_t Period_Toggle = 0 ;

int ToggleLED(int argc, char ** argv)
{

	if (argc !=2)
	{
		printf("C est 1 argument compris entre 0 et 1000 car on est presse ici\r\n"); // ATTENTION SI PAS DE \n  PRINTF STOCKER DANS TABLEAU CACHE DONC QUAND ON APPEllERA PRINTF, MEME SI ERREUR CORRIGE, CA RENVOIT CE QU IL Y A DANS CE TABLEAU, DONC CA PEUT FAIRE CROIRE QUE C EST PAS CORRIGE ALORS QUE SI
		return -1; //arrête la fonction et -1 correspond traditionnellement à une erreur.
	}
	else if (atoi(argv[1]) >= FIVE_SEC){
		printf("tu veux vraiment attendre plus de 5 secondes ?\r\n");
		return -1;
	}
	else{
		int Period_Toggle_int = atoi(argv[1]);
		Period_Toggle = (TickType_t) Period_Toggle_int;
		if (Period_Toggle == 0)
		{
			vTaskSuspend(h_task_ToggleLED);
			HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, RESET);
		}
		else{
			Period_Toggle = atoi(argv[1]);
			vTaskResume(h_task_ToggleLED);
		}
	}

	return 0;
}

TickType_t Period_Delay_msg = 0 ;
char* message = "";
int number_msg = 0 ;

int spam(int argc, char ** argv)
{
	if (argc != 4)
	{
		printf("expected three arguments \r\n");
		return -1;
	}
	int Period_Delay_msg_int = atoi(argv[3]);
	if (Period_Delay_msg_int == 0){
		vTaskSuspend(h_task_spam);
	}
	else{
		Period_Delay_msg = (TickType_t)Period_Delay_msg_int;
		message = argv[1];
		number_msg = atoi(argv[2]);
		vTaskResume(h_task_spam); //without this line the shell command line doesn't display properly
		vTaskSuspend(h_task_shell);
	}
	return 0 ;
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

/* Cette fonction est appelée si une tâche déborde de sa pile */
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    printf("critical stack overflow in task: %s\r\n", pcTaskName);
    __disable_irq();

    while(1) {
		Period_Toggle = 500;
		vTaskResume(h_task_ToggleLED);
    }
}
