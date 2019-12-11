# OPENMP Exercice 5 à 10 Florian Simon-Rouquie et Axel Houdayer
Pour compiler chaque exercices, il vous suffit d'écrire :
make [numExo]

exemple pour l'exercice 1 : make 1  

Attention, pour les exercices qui requierd un paramètre, il faut faire :
make [numExo] x=[Valeur]

exemple pour l'exercice 5 : make 5 x=10

**********************************************
Autre méthode : gcc -fopenmp exo5.c -o exo5  
puis en l'executant : ./exo5 10
en changeant le numéro (ici 5) par le numéro de l'exercice.
(ici 10 est le paramètre)
