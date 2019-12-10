#include <stdio.h> 
#include <time.h>
#include <stdlib.h>
#include <omp.h>

void ProdMatVect(int nc, int nl, double** A, double* x, double* y);
void ProdMatMat(int nc, int nl, double** A, double** B, double*** C);

int main(int argc, char **argv){   
 
 
    int nl=2,nc=2;
    int i,j;
    
    double x[nl], y[nl];
    
    double **A=(double **) malloc(sizeof(double*)*nl);
    double **B=(double **) malloc(sizeof(double*)*nl);
    double **C=(double **) malloc(sizeof(double*)*nl);
    
    #pragma omp parallel for
    for(i=0;i<nl;i++){
        A[i]=(double *) malloc(sizeof(double)*nc);
        B[i]=(double *) malloc(sizeof(double)*nc);
        C[i]=(double *) malloc(sizeof(double)*nc);
        
        for(j=0;j<nc;j++){
            A[i][j]=rand()%10;
            B[i][j]=rand()%10;
            C[i][j]=0;
        }
        x[i]=rand()%10;
        y[i]=0;
    }

    /*
    for(i=0;i<nl;i++){
        for(j=0;j<nc;j++){
             printf("A%d%d %f\n",i,j,A[i][j]);
        }
    }
    
    for(i=0;i<nl;i++){
        printf("x%d %f\n",i,x[i]);
    }
    
    ProdMatVect(nc,nl,A,x,y);
    
    for(i=0;i<nl;i++){
        printf("y%d %f\n",i,y[i]);
    }
    */
    
    for(i=0;i<nl;i++){
        for(j=0;j<nc;j++){
             printf("A%d%d %f\n",i,j,A[i][j]);
        }
    }
    
    for(i=0;i<nl;i++){
        for(j=0;j<nc;j++){
             printf("B%d%d %f\n",i,j,B[i][j]);
        }
    }
    
    ProdMatMat(nc,nl,A,B,&C);
    
    for(i=0;i<nl;i++){
        for(j=0;j<nc;j++){
             printf("C%d%d %f\n",i,j,C[i][j]);
        }
    }
    
    return 0;
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
