#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
    double temps_debut = omp_get_wtime();
    #pragma omp parallel for
    for (int i = 0; i < 5; i++) {
        printf("Bonjour le monde i = %d, depuis le thread numéro %d\n",i,omp_get_thread_num());
    }
    printf("Temps pris : %f\n",omp_get_wtime()-temps_debut);
    return 0;
}
