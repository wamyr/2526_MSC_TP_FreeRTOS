# 0.1 Premiers pas:

1) main.c est un fichier se trouvant dans le fichier source du Core
2) Les balises Begin et End permettent d'écrire du code dans des sections dédiés à stm32 aidant le processeur à initialisé des variables, appelées des fonctions etc. si on écrit en dehors et que l'on recharge l'ioc, tout le code s'efface.
3) Le paramètre à HAL_Delay(Delay) est uint32_t Delay qui est un entier non signé sur 32 bits qui correspond au temps à attendre à partir du tick du processeur dans une boucle while tandis que les paramètres de TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) sont la structure d'un Port GPIO et d'un entier non signé sur 16 bits qui correspond à la pin.
4) Ces ports d'entrées/sorties sont définis dans les fichiers .c des péréphériques, ici gpio.c pour togglepin et pour HAL_Delay c'est une entré définit par l'utilisateur sauf si c'est HAL_MAX_Delay qui est définit dans stm32g4xx_hal_def.h et vaut 0xFFFFFFFFU. 

6)On configure le NVIC du péréphérique GPIO et configure la fonction weak Callback qui est appalée lorsque l'interruption du bouton s'active.

<img width="400" height="198" alt="image" src="https://github.com/user-attachments/assets/c5a2637c-2151-4ee0-8891-3977ab27b666" /> 

# 1 FreeRTOS, tâches et sémaphores
## 1.1 Tâche simple

1) Dans la configuration du FreeRTOS il y a des paramètres pertientes comme la priorité maximal (dépend de la complexité du projet), de la taille stack ou de la fréquence de tick mais le plus pertinent à ce niveau est le HEAP_Size que l'on s'empresse d'augmenter à 20K car correspond à la mémoire dynamic pour les tâches et variables utilisés pour l'os. 
Ce qui change dans le fichier  FreeRTOSConfig.h sont les #define comme configTOTAL_HEAP_SIZE qui passe à 20K.

2)
<img width="870" height="215" alt="image" src="https://github.com/user-attachments/assets/10428047-19ad-4f14-837c-7344e5007d74" />

Rien de bien compliqué, on définit correctement la tâche, sa création et on lance le Scheduler et tout fonctionne !
Note : On utilisera un #define pour Period_Toggle plutôt... mais pour prendre la photo c'est mieux comme ça. 

La macro portTICK_PERIOD_MS renvoie la période du tick, l'interruption d'horloge utilisée par FreeRTOS, en ms.

## 1.2 Sémaphores pour la synchronisation
3) **Code :**

<img width="550" height="476" alt="image" src="https://github.com/user-attachments/assets/6d08e993-1fc1-437f-a51b-82b794061031" />

5) **Résultat :**

<img width="400" height="674" alt="image" src="https://github.com/user-attachments/assets/792271e9-4621-43de-bbf7-acbecdec5155" />

6) **En inversant les priorités :**
*TaskTake a une priorité supérieur à TaskGive*

<img width="400" height="674" alt="image" src="https://github.com/user-attachments/assets/fe05daf2-bd71-4e84-aa81-ca80dd058f7f" />

Les résultats obtenus sont cohérent. Dans le code, TaskTake renvoie une erreur si elle met plus de 1s à pouvoir récupérer un Seméphore. 
  A la première étape, (TaskGive a une priorité supérieur à TaskTake) TaskGive donne un sémaphore puis la tâche se bloque 100ms, TaskTake récupère le sémaphore, TaskGive est toujours bloqué donc TaskTake veut récupérer à nouveau un sémaphore mais ne peut pas car celui-ci vient d'être récupérer par cette même tâche. TaskTake va donc se bloquer et attends le sémaphore. 
  Au bout de 100ms, TaskGive se débloque et donne un sémaphore et se bloque pendant 200ms. Ceci 11 fois au total car TaskGive donne un sémaphore puis se bloque pendant un temps. C'est ce que l'on observe dans les screens peu importe la priorité de la tâche. La différence dans la priorité ici est quelle tâche commence.

## 1.3 Notification
7) **Code :**

<img width="400" height="385" alt="image" src="https://github.com/user-attachments/assets/52de239b-f23f-4111-81ce-95a2fc66767d" />

<img width="824" height="91" alt="image" src="https://github.com/user-attachments/assets/f491a08a-b80b-4bd9-b2db-94e4a656930d" />

**Résultat :**

<img width="400" height="618" alt="image" src="https://github.com/user-attachments/assets/64f9f2fa-7221-4167-8e55-d2cdb3d9de48" />

Cela fonctionne comme avant donc on a réussie à remplacer le sémaphore en notification.

## 1.4 Queues
8) **Résultat :**
   
   <img width="253" height="691" alt="image" src="https://github.com/user-attachments/assets/c3b679f2-0853-4392-a690-7cc266e6dddd" />

   On observe bien qu'à chaque fois que la tâche TaskGive se bloque, donc une fois que l'on envoie une notification à TaskTake, le tick a bien été envoyé et est reçu par TaskTake qui renvoie la valeur du tick et se rebloque jusqu'à la prochaine notification. 

## 1.5 Réentrance et exclusion mutuelle
9) 

<img width="281" height="55" alt="image" src="https://github.com/user-attachments/assets/27f163b5-6ead-4b9f-9e44-ddbf6e748d60" />

10) Le problème ici est que le printf n'affiche pas les mêmes valeurs de delay pour les tâches une et deux. Deux hypothèses :
- le stack_size est trop petit par rapport à ce que prend printf en mémoire et le stack_overflow crée cette erreur.
- le delay est trop petit par rapport au temps que prends printf pour transmettre sur l'uart la chaine de caractère.

  Pour vérifier ces hypothèses, on a modifié les valeurs Stack_Size et TASKi_DELAY. Résultat : le overflow n'est pas le problème car l'affichage dans le terminal ne se corrige pas mais si on augmente le delay de la tâche 2 plus prioritaire, on observe bien que l'affichage se corrige :

  <img width="295" height="61" alt="image" src="https://github.com/user-attachments/assets/ab348640-bdce-4575-8d09-8c7881cb2ef7" />

11) On va donc devoir utiliser un sémaphore Mutex pour protéger le printf tout en respectant le delay de dodo de chacune des tâches.
**Résultat :**

<img width="327" height="49" alt="image" src="https://github.com/user-attachments/assets/b3c51b6f-42a1-4bf7-b4fc-37b5e6db82af" />

Problème réglé !