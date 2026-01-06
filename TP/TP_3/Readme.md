# 3.  Debug, gestion d’erreur et statistiques

##3.1 Gestion du tas

1) & 2) La zone réservée à l'allocation dynamique est le tas (heap) de FreeRTOS et non du heap C qu'on se fera un plaisir de réduire. Cette zone est donc gérée par FreeRTOS.

3) C'était déjà pris en compte

4)

<img width="718" height="178" alt="image" src="https://github.com/user-attachments/assets/8ef272e4-5bd4-4f5e-b248-00cd5abc753d" />

5) Pour vérifier cela, on écrit une boucle while qui vérifie le statue de la création d'une tâche. Si ce statut est différent de PdPASS on sort de la boucle while. A chaque tour de boucle on incrémente une variable pour connaître le nombre de fois que l'on a créé une tâche.

Résultat :

<img width="211" height="33" alt="image" src="https://github.com/user-attachments/assets/ab7cb7de-9aaa-4858-a90a-03c18702b872" />

6) La mémoire n'a pas changé et cela est normal car la création de tâche se réalise dans la pile de manière dynamique (en utilisant xtaskcreate, on verra dans la suite du TP que xtaskcreatestatic préalloue la mémoire). Or, build analyser affiche l'état de la mémoire une fois l'allocation mémoire réalisée (static) donc ne peut afficher ce qui est allouée dans la pile après avoir flash. Pour voir l'état de la pile de FreeRTOS, il faudrait afficher xPortGetFreeHeapSize() dans le terminal.

7) & 8) On a augmenté la heap_size à 30000 bytes au lieu de 20000 bytes.

<img width="712" height="151" alt="image" src="https://github.com/user-attachments/assets/9b46b4ee-5bbe-4daa-af04-18cf7e276f2f" />

La mémoire flash est plus pleine que précédemment. En effet, comme expliqué ci-dessus, on a augmenté la heap_size donc la taille de la pile de FreeRTOS donc de manière static, c'est pourquoi cette fois-ci on observe une augmentation de la flash.

##3.2 Gestion des piles :

1) & 2) & 3) & 4) On décide de configurer CHECK_FOR_STACK_OVERFLOW à 2 car permet de vérifier si la pile de la tâche déborde. C'est une méthode qui n'est pas la plus rapide mais reste pertinente dans ce problème de de stack overflow. On écrit donc la fonction vApplicationStackOverflowHook qui est appelé si il y a une détection de débordemment de pile. Dedans on affiche dans le terminal qu'il y a un débordement de tâche et on affiche la tâche en question, on bloque les interruptions (permmet de tuer le Scheduler et figer le système car si dépasse la pile et que l'on écrit n'importe où, un actionneur pourrait lors d'une interruption lire quelque chose qui l'active)
On écrit donc la tâche task_stack_overflow où l'on tente d'allouer 2000 octets sur une pile de 1024 octets. Pour être sûr d'écraser la mémoire on va écrire dedans. 

Résultat :

<img width="268" height="34" alt="image" src="https://github.com/user-attachments/assets/11459020-0d47-43f3-96dd-34db0aacc167" />

On détecte effectivement le stack_overflow.

5) Il existe les fonctions :
**Fonction :** `void vApplicationIdleHook( void );`qui se configure avec configUSE_IDLE_HOOK. Cette fonction est appelée en boucle par la **Tâche Idle** lorsque le processeur n'a aucune autre tâche à exécuter. Elle permet de mettre le microcontrôleur en mode veille (Sleep Mode) pour économiser l'énergie et d'executer des tâches de fond à très basse priorité (clignotement de LED d'état).

**Fonction :** `void vApplicationTickHook( void );` qui se configure par configUSE_TICK_HOOK. Cette fonction est appelée à chaque **Tick d'interruption**. Elle permet d'implémenter des fonctionnalités périodiques très rapides ou une base de temps simple sans créer de tâche dédiée.

**Fonction :** `void vApplicationMallocFailedHook( void );`qui se configure avec configUSE_MALLOC_FAILED_HOOK. Appelée lorsqu'un appel à `pvPortMalloc()` (ou la création d'une tâche/queue/sémaphore) échoue par **manque de mémoire Heap**. Elle permet donc de détecter immédiatement un dimensionnement trop faible du Heap (`configTOTAL_HEAP_SIZE`) ou une fuite de mémoire.

**Fonction :** `void vApplicationDaemonTaskStartupHook( void );`qui se configure avec configUSE_DAEMON_TASK_STARTUP_HOOK. Elle est appelée une seule fois au démarrage du système, exactement au moment où la tâche Timer (Daemon Task) commence à s'exécuter. ELle permet d'exécuter du code d'initialisation qui nécessite que le scheduler soit déjà actif. Par exemple : Démarrer des Timers logiciels ou poster un événement initial.





