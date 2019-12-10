#include <stdio.h> 
#include <omp.h> 
#include <time.h>
#include <stdlib.h>

void carre(double *tab,int taille);
void print_tab(double *tab,int taille);

int main(int argc, char **argv){   
    
    srand(time(NULL));
    omp_set_num_threads(4);
   
    int i,j,taille = 10;
    
    printf("\nNbr de threas fixe\n");
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
        
        printf("temps: %3.6f s | taille: %d | nbr Threads: 4\n",omp_get_wtime()-debut,taille);
        //printf("Somme finale: %11.0f\n",somme);
        
        free(tab);;
    }
    printf("\nNbr de threas variable\n");
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
       
        printf("temps: %3.6f s | taille: 1000000 | nbr Threads: %d \n",omp_get_wtime()-debut,j);
        //printf("Somme finale: %11.0f\n",somme);
    }
    free(tab);
}



