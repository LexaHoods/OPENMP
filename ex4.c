#include <stdio.h> 
#include <omp.h> 

int i; 
#pragma omp threadprivate(i) 

int main(){   
    i = -1; 
    
    omp_set_num_threads(100);
    
    #pragma omp parallel 
    {   
        #pragma omp single copyprivate(i) 
        { 
	    i = 2; 
	} 
        printf("La valeur parallele est %d thread n: %d\n", i,omp_get_thread_num()); 
    } 
    printf("La valeur sequentielle est %d\n", i);
}

