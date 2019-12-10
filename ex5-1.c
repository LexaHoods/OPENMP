#include <stdio.h> 
#include <omp.h> 
#include <time.h>
#include <stdlib.h>

void carre(double *tab,int taille);
void print_tab(double *tab,int taille);

int main(int argc, char **argv){   
    
    srand(time(NULL));
    omp_set_num_threads(3);
   
    int i,taille = 8;//atoi(argv[1]);
    
    double tab[taille];

    //double *tab=(double *) malloc(sizeof(double)*taille);
    
    //double debut = omp_get_wtime();
    
    #pragma omp parallel for
    for(i=0;i<taille;i++){
        tab[i]=rand();
        printf("Thread: %d Charge: %d \n",omp_get_thread_num(),i);
    }
   
    //print_tab(tab,taille);
    
    carre(tab,taille);
    
    //printf("Temps pris : %f s \n",omp_get_wtime()-debut);
    //free(tab);
    //print_tab(tab,taille);
   
}

void print_tab(double *tab,int taille){
    int i;
    for(i=0;i<taille;i++){
        if(i==0){
            printf("[%f",tab[i]);
        }
        else{
            printf(",%f",tab[i]);
        }
    }
    printf("]\n");
}

void carre(double *tab,int taille){
    int i,n;
    #pragma omp parallel for
    for(i=0;i<taille;i++){
        tab[i]*=tab[i];
        n=omp_get_num_threads();
    }
    printf("Nbr de thread: %d \n",n);
}
