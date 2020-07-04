#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
    FILE *fp;
    fp = fopen("input.txt","w");
    time_t t;
    int lineas = 100000;

    int number = 10000000;
    srand((unsigned)time(&t));
    fprintf(fp, "%d\n",number);
    for (long i = 0; i < lineas; i++) {
        int random_1  = rand() % 4;
        if(random_1 == 0){
            fprintf(fp, "PREORDEN\n");
        }else if(random_1 == 1){
            fprintf(fp, "INSERTAR %d\n", rand() % number);
        }else if(random_1 == 2){
            fprintf(fp, "SUCESOR %d\n", rand() % number);
        }else{
            fprintf(fp, "BORRAR %d\n", rand() % number);
        }
    }
    fclose(fp);
    return 0;
}