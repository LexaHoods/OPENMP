#include <stdio.h> 
#include <time.h>
#include <stdlib.h>
#include <omp.h>


void ProdMatVect(int nc, int nl, double** A, double* x, double* y);
void ProdMatMat(int nc, int nl, double** A, double** B, double*** C);
void SommVectVect(int n, double* a, double* b, double** c);


int main(int argc, char **argv){   
 
    
    int nl=2,nc=2;
    
    if(argc!=1){
        nl = atoi(argv[1]);
        nc=nl;
    }
    
    int i,j;
    
    double debut,fin;
    
    double **A=(double **) malloc(sizeof(double*)*nl);
    
    double *x=(double *) malloc(sizeof(double)*nl);
    double *temp=(double *) malloc(sizeof(double)*nl);
    double *temp2=(double *) malloc(sizeof(double)*nl);
    
    #pragma omp parallel for
    for(i=0;i<nl;i++){
        A[i]=(double *) malloc(sizeof(double)*nc);
        
        for(j=0;j<nc;j++){
            A[i][j]=rand()%10;
        }
        
        x[i]=rand()%10;
        temp[i]=0;
        temp2[i]=0;
    }
    
    debut = omp_get_wtime();
    ProdMatVect(nc,nl,A,x,temp);
    SommVectVect(nl,temp,x,&temp2);
    ProdMatVect(nc,nl,A,temp2,temp);
    SommVectVect(nl,temp,x,&temp2);
    fin = omp_get_wtime();
    
    printf("\ntemps: %3.6f s\n",fin-debut);
    
    for(i=0;i<nl;i++){
        free(A[i]);
    }
    free(A);
    free(x);
    free(temp);
    free(temp2);
    
    return 0;
}

void SommVectVect(int n, double* a, double* b, double** c){
    int i;
    
    #pragma omp parallel for
    for(i=0;i<n;i++){
        (*c)[i]=a[i]+b[i];
    }
}

void ProdMatVect(int nc, int nl, double** A, double* x, double* y){
    
    int i,j;
    double somme;
    
    #pragma omp parallel for
    for(i=0;i<nl;i++){
        #pragma omp parallel for reduction(+:somme)
        for(j=0;j<nc;j++){
            somme+=A[i][j]*x[j];
        }
        y[i]=somme;
    }
}

void ProdMatMat(int nc, int nl, double** A, double** B, double*** C){
    
    int i,j,k;
    double somme;
    
    #pragma omp parallel for
    for(i=0;i<nl;i++){
        #pragma omp parallel for
        for(j=0;j<nc;j++){
            somme=0;
            #pragma omp parallel for reduction(+:somme)
            for(k=0;k<nl;k++){
                somme+=A[i][k]*B[k][j];
            }
            (*C)[i][j]=somme;
        }
    }
}
