//Exercice 5 , Axel Houdayer IATIC 4

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

void carre(int * array, int size);
void affichage(int * array, int size);

int main(int argc, char ** argv) {

    omp_set_num_threads(5); //Permet de parametrer le nombre de threads

    double T0 = omp_get_wtime(); //Temps d'execution

    srand(time(NULL));

    int * tab;

    int taille = atoi(argv[1]); // a) permet de lire la taille du tableau sur la ligne de commande
    int i;

    // remplit le tableau en parallele :
    tab = (int*) malloc(sizeof(int) * taille);

    #pragma omp parallel for
    for(i = 0; i<taille; i++) {
        tab[i] = rand()%20;
        printf("Nombre de thread  crées par OpenMP: %d \n ",omp_get_num_threads());
    }

    affichage(tab, taille);
    //b)Fonction qui calcule le carré de la valeur de chacun de ses éléments
    carre(tab, taille);
    //Affichage du résultat
    affichage(tab, taille);

    printf("Prends %f ms en temps d'execution\n", (omp_get_wtime() - T0) * 1000);
}


void carre(int * tab, int taille) {
    int i;
    //parallèlisation de la boucle for
    #pragma omp parallel for
    for(i = 0; i<taille; i++) {
        tab[i] = tab[i] * tab[i];
    }
}

//Fonction qui permet d'afficher les valeurs du tableau
void affichage(int * array,int size) {
    for(int i = 0; i<size; i++) {
        printf("%d \t", array[i]);
    }
    printf("\n");

}
/*
d) Si on ne définis pas le nombre de threads (grâce à la commande omp_set_num_threads(10))
    on remarque que le programme s'execute avec 4 threads par défaut.

Jeu de test :
(gcc Exo5.c -o Exo5 -fopenmp)
./Exo5 10 :
Nombre de thread  crées par OpenMP: 1
15 	2 	17 	13 	13 	19 	5 	18 	14 	11
225 	4 	289 	169 	169 	361 	25 	324 	196 	121
Prends 0.153338 ms en temps d'execution

./Exo5 10 :
Nombre de thread  crées par OpenMP: 4
9 	9 	13 	2 	8 	10 	10 	17 	2 	6
81 	81 	169 	4 	64 	100 	100 	289 	4 	36
Prends 0.816962 ms en temps d'execution

./Exo5 10 :
Nombre de thread  crées par OpenMP: 5
12 	18 	2 	6 	19 	5 	9 	19 	17 	19
144 	324 	4 	36 	361 	25 	81 	361 	289 	361
Prends 1.125846 ms en temps d'execution


./Exo5 10 :
Nombre de thread  crées par OpenMP: 10
9 	14 	1 	4 	0 	9 	10 	5 	2 	15
81 	196 	1 	16 	0 	81 	100 	25 	4 	225
Prends 1.359946 ms en temps d'execution

e) On remarque que plus le nombre de threads augmente, plus le temps d'éxecution augmente.
f) On peut aussi définir le nombre de thread en modifiant la variable d'environnement
    avec :  set OMP_NUM_THREADS=16
*/
