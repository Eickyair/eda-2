#include<stdio.h>
#include<omp.h>
int main(){
    int tmp=0;
    /**
    Obtención del segmento que acumula la mayor suma, todos comienzan en 0
    gracias a firstprivate
    */
    int n = omp_get_max_threads();
    omp_set_num_threads(n);
    int MAX[n];
    #pragma omp parallel firstprivate(tmp)
    {
        int id = omp_get_thread_num();
        #pragma omp for
        for (int i = 0; i < 1000; i++)
        {
            tmp += i;
        }
        MAX[id] = tmp;
    }
    int m=0;
    for (int i = 0; i < n; i++)
    {
        if(MAX[i] > m) m = MAX[i];
    }
    printf("m: %d\n", m);
    return 0;
}