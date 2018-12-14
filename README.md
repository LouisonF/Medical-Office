Consignes de compilation:
Ce projet a été développé à l'aide d'eclipse. De fait, le makefile a été généré automatiquement.

Installation de sqlite3:
Tuto expliquant l'installation de sqlite3:
https://www.tutorialspoint.com/sqlite/sqlite_installation.htm

Pour une installation plus facile, les fichiers sqlite3.h et sqlite3ext.h sont disponibles dans le dossier executable. Il suffit alors de le copier dans usr/local/include.

Les étapes pour build manuellement le projet sont les suivantes.

Ouvrir un terminal dans le dossier Release et lancer la commande:
make clean all

--------------------------------------------------------------------------------
Un executable du programme est disponible dans le dossier executable
Le fichier de la base de donnée avec le jeux de donnée de test est également
présent dans le dossier executable.
Si l'on désire le supprimer totalement, il faut dé-commenter une ligne dans le
main du programme compiler, lancer le programme et ensuite la re-commenter puis
recompiler pour le prochain lancement du programme.
Cette manipulation n'a pas besoin d'être réalisée en théroie, nous fournissons
un jeux de donnée de base.
