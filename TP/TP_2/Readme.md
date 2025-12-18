# 2. On joue avec le Shell :

1)  Cf le TD vu avec vous !
   
2) Il est important de définir les priorités de configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY ou augmenter la priorité des interruptions de l'USART1. En effet, nous voulons pouvoir communiquer avec la carte par le shell et cela se fait (dans notre cas) par interruption de l'USART1. Cependant, si l'interruption préempte sur le fonctionnement de FreeRTOS, on peut faire planter celui-ci. Pour cela, d'après la définition du paramètre configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY, il faut que la priorité d'interruption matérielle de l'Usart 1 soit supérieur ou égale à configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY. Ainsi, un API de FreeRTOS pourra être appelé par l'interruption de L'USART1 comme dans la tâche Shell qui utilise xQueueSendFromISR.

3) La stratégie adoptée ici est de crée une tâche qui se suspend elle même pour éviter de faire clignoter la Led tant que l'on ne l'a pas demandé (on a forcé la Led à s'éteindre par la même occasion). Lorsque l'on appel la fonction Toggle_Led avec une fréquence cohérente, la fonction réactive la tâche et fait clignoter la Led. Si la fréquence est 0, on reset l'état de la pin de la Led (on l'éteint), et on suspend la tâche.  

4) On reprend la même stratégie ici, la différence va être sur l'affichage. Lorsque l'on appel la fonction spam et donc que l'on active la tâche spam, on doit bloquer le shell, autrement le '> ' s'affichait avant le spam. On aurait faire cela autrement par le biais de notification notamment si le spam est utilisé autrement comme dans la réception de donnée de capteurs. 

En bloquant la tâche Shell :

![WhatsApp Image 2025-12-18 at 09 20 32](https://github.com/user-attachments/assets/86d79302-400e-4623-b364-eaa418dee6b9)

Sans bloquer la tâche Shell :

![WhatsApp Image 2025-12-18 at 09 27 51](https://github.com/user-attachments/assets/2962e4b9-c347-43ce-9683-0450d5b2c79a)
