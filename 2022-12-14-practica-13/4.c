#include<stdio.h>
#include <omp.h>

static long num_steps = 1000000;
double step;

int main(){
    int i;
    double x=0,pi=0;
    int m = omp_get_max_threads();
    omp_set_num_threads(m);
    step = 1.0 / (double)num_steps;
    #pragma omp parallel for reduction(+ : pi) firstprivate(step) firstprivate(x)
    for(i=0;i<num_steps;i++){
        x += (m*step);
        pi = pi + 4.0/(1.0+x*x)*step;
    }
    printf("PI = %f\n",pi);
}

