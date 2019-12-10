#include <stdio.h>
#include <omp.h>
#define X 100

int main(){

    int i = -1; 
    
    
    printf("Thread main n: %2d\n", omp_get_thread_num()); 
    printf("La valeur de la variable locale dans la région séquentielle est : %2d\n", i); 
    
    omp_set_num_threads(5); 
    
    #pragma omp parallel 
    {  
	int j; 
	//int i;
        i = omp_get_thread_num(); 
        for(j=0;j<X;j++){
	    printf("La valeur de la variable locale dans la région parallèle est : %2d\n", i); 
	}

    } 
    
    printf("Thread main du n: %2d\n", omp_get_thread_num()); 
    printf("La valeur de la variable locale dans la région séquentielle est %2d\n", i);
     
    return 0;

}

