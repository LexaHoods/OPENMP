#include <stdio.h> 
#include <omp.h> 
#include <time.h>
#include <stdlib.h>

void carre(double *tab,int taille);
void print_tab(double *tab,int taille);

int main(int argc, char **argv){   
    
    srand(time(NULL));
    int nbr_thread=4;
    omp_set_num_threads(nbr_thread);
   
    int i,j,taille = 10;
    
    printf("\nTaille variable, Nbr de threas fixe: %d\n",nbr_thread);
    for(taille=10;taille<10000000;taille*=10){
        
        double *tab=(double *) malloc(sizeof(double)*taille);
        
        double debut = omp_get_wtime();
        
        double somme;
        
        #pragma omp parallel for
        for(i=0;i<taille;i++){
            tab[i]=rand();
        }
       
        #pragma omp parallel for reduction(+:somme)
        for(i=0;i<taille;i++){
            somme+=tab[i];
            //printf("Thread: %d s: %11.0f i: %11.0f\n",omp_get_thread_num(),somme,tab[i]);
        }
        
        printf("temps: %3.6f s | taille: %d\n",omp_get_wtime()-debut,taille);
        //printf("Somme finale: %11.0f\n",somme);
        
        free(tab);;
    }
    printf("\nNbr de threas variable, taille fixe: %d\n",taille);
    taille=1000000;
    double *tab=(double *) malloc(sizeof(double)*taille);
    
    for(j=1;j<100;j+=20){
        
        omp_set_num_threads(j);
        
        double somme;
        
        double debut = omp_get_wtime();
        
        #pragma omp parallel for
        for(i=0;i<taille;i++){
            tab[i]=rand();
        }
       
        #pragma omp parallel for reduction(+:somme)
        for(i=0;i<taille;i++){
            somme+=tab[i];
            //printf("Thread: %d s: %11.0f i: %11.0f\n",omp_get_thread_num(),somme,tab[i]);
        }
       
        printf("temps: %3.6f s | nbr Threads: %d \n",omp_get_wtime()-debut,j);
        //printf("Somme finale: %11.0f\n",somme);
    }
    free(tab);
}


/*

Les courbes de performances sont en annexes 

Pour afficher les sommes partielles et totales, il faut decommenter 
les lignes 34,38, 62 et 66

Jeu de test :
gcc -fopenmp -Werror ex5-2.c -o ex5-2.out
./ex5-2.out 
ou bien
make 5-2

Taille variable, Nbr de threas fixe: 4
temps: 0.000420 s | taille: 10
temps: 0.000062 s | taille: 100
temps: 0.001131 s | taille: 1000
temps: 0.026808 s | taille: 10000
temps: 0.060773 s | taille: 100000
temps: 0.112253 s | taille: 1000000

Nbr de threas variable, taille fixe: 10000000
temps: 0.043156 s | nbr Threads: 1 
temps: 0.143510 s | nbr Threads: 21 
temps: 0.155096 s | nbr Threads: 41 
temps: 0.181844 s | nbr Threads: 61 
temps: 0.167035 s | nbr Threads: 81 


*/
