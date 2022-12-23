#include<stdio.h>
#include<omp.h>
int main(){
    int tmp = -1;
    #pragma omp parallel private(tmp)
    {
        tmp = omp_get_thread_num();
        printf("tmp_bloque_paralelo:%d\n", tmp);
        #pragma omp for
        for (int i = 0; i < 1000; i++){
            tmp += i;
        }
        printf("tmp_suma: %d por el hilo: %d\n", tmp,omp_get_thread_num());
    }
    printf("tmp:%d\n", tmp);
    return 0;
}