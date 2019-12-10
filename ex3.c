#include <stdio.h>
#include <omp.h>

int i;

int main(){

    i=-1; 
    
    #pragma omp parallel private(i)
    { 
        printf("La valeur parallele est %d\n", i); 
    } 
    printf("La valeur sequentielle est %d\n", i); 
     
    return 0;

}

