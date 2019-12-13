#include <stdio.h> 
#include <omp.h> 
#include <time.h>
#include <stdlib.h>

void carre(double *tab,int taille);
void print_tab(double *tab,int taille);

int main(int argc, char **argv){   
    
    srand(time(NULL));
    omp_set_num_threads(3);
   
    int i,taille;
    
    if(argc!=1){
        taille = atoi(argv[1]);
    }
    
    double tab[taille];

    double debut = omp_get_wtime();
    
    #pragma omp parallel for
    for(i=0;i<taille;i++){
        tab[i]=rand();
        //printf("Thread: %d Charge: %d \n",omp_get_thread_num(),i);
    }
    
    printf("Temps pris statique: %f s \n",omp_get_wtime()-debut);
    
    double *tab2=(double *) malloc(sizeof(double)*taille);
    
    debut = omp_get_wtime();
    
    #pragma omp parallel for
    for(i=0;i<taille;i++){
        tab2[i]=rand();
        //printf("Thread: %d Charge: %d \n",omp_get_thread_num(),i);
    }
    
    printf("Temps pris dynamique: %f s \n",omp_get_wtime()-debut);
    
    free(tab2);
    //print_tab(tab,taille);
   
}

/*
En dynamique chaque threads prend en charge n/m cases du tableau, si le
resultat de la division euclidienne vaut r et n'est pas nul,
les threads de 0 à r prennent en charge chacun une case supplementaire.

L'utilisation d'un tableau dynamique ne change rien a la charge mais reduit 
le tmps de calcul


Jeu de test :
(gcc exo5-1.c -o exo5-1 -fopenmp)
./exo5-1  ou make 5-1  
Temps pris statique: 0.001016 s 
Temps pris dynamique: 0.001259 s 

Ou bien
make 5-1 x=1000000
Temps pris statique: 0.092939 s 
Temps pris dynamique: 0.111287 s 


*/
