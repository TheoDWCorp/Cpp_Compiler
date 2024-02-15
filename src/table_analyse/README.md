# Générer un automate et une table d'analyse

## Avec la grammaire du sujet
La grammaire du sujet se situe dans grammaires/grammaire_sujet_raw.txt
Pour l'utiliser il faut d'abord passer le lexeur dessus pour récupérer les tokens
```
make grammaire_sujet_modifier
./grammaire_sujet_modifier
```
La grammaire modifié est enregistré dans grammaires/grammaire_sujet.txt
Pour générer l'automate et la table d'analyse il faut executer les commandes suivantes
Pour choisir cette grammaire il faut ecrire son path dans create_grammaire.cpp et écrire le bon non terminal augmente dans ce meme fichier
```
make create_automate
./create_automate
```
## Avec une autre grammaire
Pour choisir cette grammaire il faut ecrire son path dans create_grammaire.cpp et écrire le bon non terminal augmente dans ce meme fichier
```
make create_automate
./create_automate
```

# Les fichiers de sortie
Il y a trois fichiers de sortie différents, table_analyse.csv, table_analyse_conflis.csv et liste_reduction.txt
Pour les automates de moins de 100 états un diagramme uml est généré et enregistré dans Automate.png