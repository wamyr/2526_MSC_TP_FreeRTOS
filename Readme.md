<img width="573" height="285" alt="image" src="https://github.com/user-attachments/assets/c5a2637c-2151-4ee0-8891-3977ab27b666" />0.1 Premiers pas: 
main.c est un fichier se trouvant dans le fichier source du Core
Les balises Begin et End permettent d'écrire du code dans des sections dédiés à stm32 aidant le processeur à initialisé des variables, appelées des fonctions etc. si on écrit en dehors et que l'on recharge l'ioc, tout le code s'efface.
Le paramètre à HAL_Delay(Delay) est uint32_t Delay qui est un entier non signé sur 32 bits qui correspond au temps à attendre à partir du tick du processeur dans une boucle while tandis que les paramètres de TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) sont la structure d'un Port GPIO et d'un entier non signé sur 16 bits qui correspond à la pin.
Ces ports d'entrées/sorties sont définis dans les fichiers .c des péréphériques, ici gpio.c pour togglepin et pour HAL_Delay c'est une entré définit par l'utilisateur sauf si c'est HAL_MAX_Delay qui est définit dans stm32g4xx_hal_def.h et vaut 0xFFFFFFFFU. 
<img width="573" height="285" alt="image" src="https://github.com/user-attachments/assets/4d2bfda2-3023-4646-8bec-faa0c0d5e957" />
On configure le NVIC du péréphérique GPIO et configure la fonction weak Callback qui est appalée lorsque l'interruption du bouton s'active.

1 FreeRTOS, tâches et sémaphores
Dans la configuration du FreeRTOS il y a des paramètres pertientes comme la priorité maximal (dépend de la complexité du projet), de la taille stack ou de la fréquence de tick mais le plus pertinent à ce niveau est le HEAP_Size que l'on s'empresse d'augmenter à 20K car correspond à la mémoire dynamic pour les tâches et variables utilisés pour l'os. 
Ce qui change dans le fichier  FreeRTOSConfig.h sont les #define comme configTOTAL_HEAP_SIZE qui passe à 20K.

1.1 Tâche simple

<img width="870" height="215" alt="image" src="https://github.com/user-attachments/assets/10428047-19ad-4f14-837c-7344e5007d74" />

Rien de bien compliqué, on définit correctement la tâche, sa création et on lance le Scheduler et tout fonctionne !
Note : On utilisera un #define pour Period_Toggle plutôt... mais pour prendre la photo c'est mieux comme ça. 

La macro portTICK_PERIOD_MS renvoie la période du tick, l'interruption d'horloge utilisée par FreeRTOS, en ms.

1.2 Sémaphores pour la synchronisation
code :
<img width="719" height="622" alt="image" src="https://github.com/user-attachments/assets/6d08e993-1fc1-437f-a51b-82b794061031" />
résultat : 
<img width="518" height="876" alt="image" src="https://github.com/user-attachments/assets/792271e9-4621-43de-bbf7-acbecdec5155" />
En inversant les priorités :
<img width="504" height="803" alt="image" src="https://github.com/user-attachments/assets/fe05daf2-bd71-4e84-aa81-ca80dd058f7f" />
Il faudra commenter pourquoi. (à la fin TaskTake a une priorité > TaskGive)

1.3 Notification
code :
<img width="713" height="687" alt="image" src="https://github.com/user-attachments/assets/52de239b-f23f-4111-81ce-95a2fc66767d" />
<img width="824" height="91" alt="image" src="https://github.com/user-attachments/assets/f491a08a-b80b-4bd9-b2db-94e4a656930d" />
résultat :
<img width="522" height="806" alt="image" src="https://github.com/user-attachments/assets/64f9f2fa-7221-4167-8e55-d2cdb3d9de48" />
Cela fonctionne comme avant donc on a réussie à remplacer ke sémaphore en notification.





