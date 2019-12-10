#include <stdio.h> 
#include <omp.h> 
#include <time.h>
#include <stdlib.h>

void carre(double *tab,int taille);
void print_tab(double *tab,int taille);

int main(int argc, char **argv){   
    
    srand(time(NULL));
   
    
    int i,j;
    //int m=4;
    int nl=1000,nc=1000; //attention <1000
    
    //omp_set_num_threads(m);

    
    printf("\nTableau statique\n");
    double t[nl][nc];
    
    //debut = omp_get_wtime();
    
    //#pragma omp parallel for
    for(i=0;i<nl;i++){
        for(j=0;j<nc;j++){
            //printf("%d-%d\n",i,j);
            t[i][j]=rand();
        }
    }
    //fin = omp_get_wtime();
    
    printf("%f\n",t[0][0]);
    
    //printf("temps: %3.6f s\n",fin-debut);
    
    
    printf("\nTableau dynamique\n");
    
    double **tab=(double **) malloc(sizeof(double*)*nl);
    for(i=0;i<nl;i++){
        tab[i]=(double *) malloc(sizeof(double)*nc);
    }
    
    //double debut = omp_get_wtime();
    
    //#pragma omp parallel for
    for(i=0;i<nl;i++){
        for(j=0;j<nc;j++){
            //printf("%d-%d\n",i,j);
            tab[i][j]=rand();
        }
    }
    
    //double fin = omp_get_wtime();
    
    //printf("temps: %3.6f s\n",fin-debut);
    
    for(i=0;i<nl;i++){
        free(tab[i]);
    }
    free(tab);
        
    return 0;
}



