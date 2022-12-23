#include<stdio.h>
#include "omp.h"
#define NUM_STEPS 1000000

int main(){
    int max = omp_get_max_threads();
    omp_set_num_threads(max);
    double s = 0.0;
    double sum[max];
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        double diferencial = 1.0/NUM_STEPS;
        double step = (double)max*diferencial;
        double x = (double)id*diferencial;
        double sub_sum = 0.0;
        while(x<=1.00000){
            double fx = 4.0/(1+(x*x));
            double area = diferencial*fx;
            sub_sum+=area;
            x+=step;
        }
        sum[id]=sub_sum;
    }
    int i = 0;
    while(i<max){
        s+=sum[i];
        i+=1;
    }
    printf("Pi:%f\n",s);
    return 0;
}
