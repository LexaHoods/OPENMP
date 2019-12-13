#include <stdio.h> 
#include <time.h>
#include <stdlib.h>
#include <omp.h>

void ProdMatVect(int nc, int nl, double** A, double* x, double* y);
void ProdMatMat(int nc, int nl, double** A, double** B, double*** C);

int main(int argc, char **argv){   
 
 
    int nl=2,nc=2;
    
    if(argc!=1){
        nl = atoi(argv[1]);
        nc=nl;
    }
    
    int i,j;
    double debut,fin;
    
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

    printf("\nProduit Matrice Vecteur \n");
    for(i=0;i<nl;i++){
        for(j=0;j<nc;j++){
             printf("A%d%d %f\n",i,j,A[i][j]);
        }
    }
    for(i=0;i<nl;i++){
        printf("x%d %f\n",i,x[i]);
    }
    
    debut = omp_get_wtime();
    ProdMatVect(nc,nl,A,x,y);
    fin = omp_get_wtime();
    
    for(i=0;i<nl;i++){
        printf("y%d %f\n",i,y[i]);
    }
    
    printf("\ntemps: %3.6f s\n",fin-debut);
    
    
    printf("\nProduit Matrice Matrice \n");
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
    
    debut = omp_get_wtime();
    ProdMatMat(nc,nl,A,B,&C);
    fin = omp_get_wtime();
    
    for(i=0;i<nl;i++){
        for(j=0;j<nc;j++){
             printf("C%d%d %f\n",i,j,C[i][j]);
        }
    }
    
    printf("\ntemps: %3.6f s\n",fin-debut);
    
    for(i=0;i<nl;i++){
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);
    
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


/*
gcc -fopenmp -Werror ex7.c -o ex7.out
./ex7.out 
ou bien make 7 ou bien make 7 x=2

Produit Matrice Vecteur 
A00 3.000000
A01 7.000000
A10 5.000000
A11 2.000000
x0 3.000000
x1 1.000000
y0 16.000000
y1 17.000000

temps: 0.000007 s

Produit Matrice Matrice 
A00 3.000000
A01 7.000000
A10 5.000000
A11 2.000000
B00 6.000000
B01 5.000000
B10 6.000000
B11 9.000000
C00 60.000000
C01 78.000000
C10 42.000000
C11 43.000000

temps: 0.000012 s
*/
