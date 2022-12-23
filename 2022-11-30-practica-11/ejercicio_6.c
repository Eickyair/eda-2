#include<stdio.h>
#include "omp.h"

float big_job(int x){
    int top = (x+1)*1000;
    int primos[top+1];
    int i;
    int contP = 0;
    for(i = 2;i<=top;i++){
        int divisores = 2;
        int j;
        for(j=2;j<i;j++){
            if(i%j==0){
                divisores++;
            }
        }
        if(divisores==2){
            primos[contP]=i;
            contP+=1;
        }
    }
    float promedio = 0.0;
    i = 0;
    for(i;i<contP;i+=1){
        promedio+=primos[i];
    }
    return promedio/contP;
}

float consume(float B){
    int num_steps = 300000;
    double step;

    int i;
    double x,res,sum = 0.0;
    step = B/(double)num_steps;
    for(i=0;i<num_steps;i++){
        x = (i+0.5)*step;
        sum = sum + 4.0/(1.0+x*x);
    }
    res = step*sum;
    return res;
}

int main(){
    int niters = 10;
    float res = 0;
    #pragma omp parallel
    {
        float B;
        int i,id,nthrds;
        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();
        for(i=id;i<niters;i+=nthrds){
            B = big_job(i);
            //printf("id:%d B:%f\n",id,B);
            #pragma omp critical
            res += consume(B);
        }
    }
    printf("res = %f\n",res);
    return 0;
}
