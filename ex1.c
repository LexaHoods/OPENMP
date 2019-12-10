#include <stdio.h>
#include <omp.h>

int main(){

    omp_set_num_threads(3);

    double debut = omp_get_wtime();
  
    #pragma omp parallel
    {
      int i;
      for(i=0;i<5;i++){
        printf("Thread numero:%d iteration:%d \n",omp_get_thread_num(),i);
      }
    #pragma omp barrier
    }
    
    printf("Temps pris : %f s \n",omp_get_wtime()-debut);
    return 0;
}
