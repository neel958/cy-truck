# CY-TRUCK Naël AHMED, Rayan HUSSEIN, Adel Smaïli


**Projet fin semestre 3 informatique Mi-03**

Vous pouvez télécharger le dossier à partir de github directement, une fois cela fait n'oubliez pas de vous accorder les droits d'execution en utilisant la commande suivante : 
`chmod 777 projet.sh`.
Assurez vous d'avoir le fichier data csv dans le dossier.
Afin d'executer le programme complet, tappez juste la commande suivante dans un terminal `make`, assurez vous d'etre dans le meme dossier que le makefile.

Afin de lancer la commande help, tappez le code suivant : `./projet.sh data.csv -h`

Pour supprimer les fichiers executables, tappez la commande suivante : `make -f make clean`

**Problème rencontrés :**

Le traitement T rencontrait beaucoup de soucis, nous l'avons donc retiré du code, il n y a donc pas de traitement T de disponible, de + le traitement S rencontre aussi certains problème, il se peut que les valeurs inscrites dans le fichier final ne correspondent pas forcement aux résultats attendus. 

De plus, le makefile rencontre un soucis lors de la compilation, afin d'executer le programme, il faut donc saisir la commande `./projet.sh data.csv -X`où X est le traitement voulu, il faut bien que le fichier data.csv soit dans le meme dossier que le projet.
