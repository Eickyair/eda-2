#include<stdio.h>
#include "omp.h"

long long num_steps = 1000000;
double step;

int main(){
    int i;
    double x,pi,sum = 0.0;
    step = 1.0/(double)num_steps;
    double inicio = omp_get_wtime();
    for(i=0;i<num_steps;i++){
        x = (i+0.5)*step;
        sum = sum + 4.0/(1.0+x*x);
    }
    double fin = omp_get_wtime();
    pi = step*sum;
    printf("PI = %f Time = %f\n",pi,fin-inicio);
}
