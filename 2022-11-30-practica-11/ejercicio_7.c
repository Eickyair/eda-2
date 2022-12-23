#include<stdio.h>
#include "omp.h"
double seed = 2.0;
int num_steps = 1000000;

double getNumber(){
    double num = seed;
    //print("%d",RAND_MAX);
    seed*=3.0;
    return num;
}

double funBig(double B){
    double x,res,step,sum = 0.0;
    //printf("%f\n",B);
    step = B/(double)num_steps;
    int i;
    for(i=0;i<num_steps;i++){
        x = (i+0.5)*step;
        sum = sum + (x*x*x);
    }
    res = step*sum;
    return res;
}
int main(){
    double A = 0;
    float res;
    #pragma omp parallel
    {
        double tmp,B;
        B = getNumber();
        tmp = funBig(B);
        //printf("tmp:%f\n",tmp);
        #pragma omp atomic
        A+=tmp;
    }
    printf("A:%f\n",A);
    return 0;
}
