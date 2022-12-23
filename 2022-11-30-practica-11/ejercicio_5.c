#include<stdio.h>
#include "omp.h"
#define NUM_THREADS 4

int big_call(int id){
    int top = (id+1)*1500;
    int i;
    int contNumerosPrimos = 0;
    for(i = 2;i<=top;i++){
        int divisores = 2;
        int j;
        for(j=2;j<i;j++){
            if(i%j==0){
                divisores++;
            }
        }
        if(divisores==2){
            contNumerosPrimos++;
        }
    }
    return contNumerosPrimos;
}
int big_call2(int id){
    unsigned int top = (id+1)*1e7;
    int i;
    int s = 0;
    for(i=0;i<top;i++){
        s+=i;
        s%=((int)1e9+7);
    }
    return s;

}

int main(){
    omp_set_num_threads(NUM_THREADS);
    int A[NUM_THREADS], B[NUM_THREADS];
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        A[id] = big_call(id);
        //printf("Thread_id:%d\n",id);
        #pragma omp barrier
        //printf("BARRIER - Thread_id:%d\n",id);
        B[id] = big_call2(id);
    }
    int i;
    for(i=0;i<NUM_THREADS;i++){
        printf("A:%d B:%d\n",A[i],B[i]);
    }
    return 0;
}
