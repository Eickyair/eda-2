#include<stdio.h>
#include<omp.h>
char *lastNames[] = {
    "Casillas",
    "Rosas",
    "Montelongo",
    "Ortiz"
};
char *streets[] = {
    "Calle 1",
    "Calle 2",
    "Calle 3",
    "Calle 4"
};
char *names[] = {
    "Luis",
    "Camila",
    "Pablo",
    "Mitzi"
};
int ages[] = {18,20,32,19};
void getName(int userId){
    printf("request made to the db...\n");
    printf("%s\n",names[userId]);
}
void getStreet(int userId){
    printf("request made to the db...\n");
    printf("%s\n",streets[userId]);
}
void getAge(int userId){
    printf("request made to the db...\n");
    printf("%d\n",ages[userId]);
}
void getLastName(int userId){
    printf("%s",lastNames[userId]);
}

int userId;
#pragma omp threadprivate(userId)
int main(){
    #pragma omp parallel
    {
        #pragma omp master
        userId  = omp_get_thread_num();
        #pragma omp barrier
        #pragma omp sections
        {
            #pragma omp section
            getName(userId);
            #pragma omp section
            getStreet(userId);
            #pragma omp section
            getAge(userId);
        }
    }
    getLastName(userId);
    return 0;
}