#include <stdio.h> 
#include <omp.h> 
#include <time.h>
#include <stdlib.h>

void carre(int *tab,int taille);
void print_tab(int *tab,int taille);

int main(int argc, char **argv){   
    
    srand(time(NULL));
    //omp_set_num_threads(10);
   
    int i,taille = atoi(argv[1]);

    int *tab;
    
    tab=(int *) malloc(sizeof(int)*taille);
    
    double debut = omp_get_wtime();
    //time_t debut =time(NULL);
    
    #pragma omp parallel for
    for(i=0;i<taille;i++){
        tab[i]=rand()%20;
    }
   
    carre(tab,taille);
    
    printf("Temps pris : %f s \n",omp_get_wtime()-debut);
    //printf("Temps pris : %ld s \n",time(NULL)-debut);
    
    //printf("Nbr de coeur : %d \n",omp_get_num_procs());
    
    //print_tab(tab,taille);
    free(tab);
   
}

void print_tab(int *tab,int taille){
    int i;
    for(i=0;i<taille;i++){
        if(i==0){
            printf("[%d",tab[i]);
        }
        else{
            printf(",%d",tab[i]);
        }
    }
    printf("]\n");
}

void carre(int *tab,int taille){
    int i;
    #pragma omp parallel for
    for(i=0;i<taille;i++){
        tab[i]*=tab[i];
    }
    printf("Nbr de thread: %d \n",omp_get_num_threads());
}
