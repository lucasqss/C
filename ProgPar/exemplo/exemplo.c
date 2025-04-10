//Adaptado de https://github.com/gpsilva2003/OPENMP/blob/main/src/omp_parfor.c

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

void saxpy(long n, float a, float * restrict x, float * restrict y)
{
#pragma omp parallel for
    for (long i = 0; i < n; ++i){
        printf("Numero thread = %d \n", omp_get_thread_num());
        y[i] = a*x[i] + y[i];
    }
}

int main(int argc, char *argv[]) { /* omp_parfor.c  */
    long n = 100; // 1 milhão de floats
    float *x = (float*)malloc(n*sizeof(float));
    float *y = (float*)malloc(n*sizeof(float));
#pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        x[i] = 2.0f;
        y[i] = 1.0f;
    }
    saxpy(n, 3.0f, x, y);
    free(x);
    free(y);
    return(0);
}