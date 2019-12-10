#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
omp_lock_t lock;

double calcul(double* array, int length);
void remplissage(double* array, int length);
void affichage(double * array, int size);
int main()
{
    double T0 = omp_get_wtime();
    srand(time(NULL));
    double array[1024],total;
    remplissage(array,1024);
    affichage(array,5);
    omp_init_lock(&lock);
    total=calcul(array,1024);
    omp_destroy_lock(&lock);
    printf("Total = %f\n",total);
    printf("Prends %f ms en temps d'execution en total\n", (omp_get_wtime() - T0) * 1000);

}
void remplissage(double* array, int length){
    #pragma omp parallel for
    for(int i = 0; i<length; i++) {
        array[i] = rand()%20;
    }
}
double calcul(double* array, int length){
    double T0 = omp_get_wtime();
    double total = 0.0;
    #pragma omp parallel for
        for(int i = 0; i < length; i++) {
            omp_set_lock(&lock);
            total+=array[i];
            omp_unset_lock(&lock);

    }
    printf("Prends %f ms en temps d'execution pour le calcul\n", (omp_get_wtime() - T0) * 1000);

    return total;
}
void affichage(double * tab,int taille) {
    for(int i = 0; i<taille; i++) {
        printf("%f ", tab[i]);
    }
    printf("\n");

}
