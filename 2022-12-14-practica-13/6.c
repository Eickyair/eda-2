#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

#define MAX 1000
int **Matrix(int r,int c){
    int **A = (int **)malloc(sizeof(int*)*r);
    #pragma omp parallel for
    for (int i = 0; i < r;i++){
        A[i] = (int *)malloc(sizeof(int) * c);
    }
    return A;
}

void init(int **M,int r, int c){
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < r;i++){
        for (int j = 0; j < c;j++){
            M[i][j] = 1;
        }
    }
}

void debug(int **M,int r,int c){
    for(int i = 0;i<r;i++){
        printf("|");
        for(int j = 0;j<c;j++){
            printf("%d ",M[i][j]);
        }
        printf("|\n");
    }
}

void nillM(int **X,int r,int c){
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            X[i][j]=0;
        }
    }
}
int RA = MAX, CA = MAX;
int RB = MAX, CB = MAX;

void multiply(int **A,int **B, int **C){
    int i,j,k;
    for(i=0;i<RA;i++){
        for(j=0;j<CB;j++){
            for(k=0;k<CA;k++){
                C[i][j]+=A[i][k]*B[k][j];
            }
        }
    }
}


double ini,end;
int main(){
    int RC = RA, CC = CB;
    int **A = Matrix(RA,CA);
    int **B = Matrix(RB,CB);
    int **C = Matrix(RC,CC);
    nillM(C,RC,CC);
    init(A,RA,CA);
    init(B,RB,CB);
    ini = omp_get_wtime();
    multiply(A,B,C);
    end = omp_get_wtime();
    // debug(C,RC,CC);
    printf("Serial:%f\n",end-ini);
    return 0;
}
