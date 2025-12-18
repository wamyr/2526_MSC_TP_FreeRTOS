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



