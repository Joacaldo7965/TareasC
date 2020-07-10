#include "ADT_List.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mallok(){
    return;
}

void freee(){
    return;
}

int empty(tLista *L){
    return 0;
}


int main(int argc, char const *argv[]){

    // Sacamos los datos del binario

    FILE *fp;
    long M;
    long N;

    fp = fopen("example1.dat", "r");
    if (fp == NULL){
        printf("Error al abrir el archivo.\n");
        exit(1);
    }
    
    fscanf(fp,"%ld",&M);
    fscanf(fp,"%ld",&N);


    // Init Lists
    tLista *L1 = malloc(sizeof(tLista));
    tLista *L2 = malloc(sizeof(tLista));

    initList(L1); insert2(L1, 1, M); // init Lista 1 con nodo inicial
    // TODO: Inicializar lista con [1, M] kappa
    
    initList(L2);                   // init Lista 2 vacia

    printList(L1);

    printList(L2);

    

    char command[7];
    char number_str[11];


    // ¿Utilizar for i < N ?? 
    while (!feof(fp)){
        fscanf(fp,"%s", command);
        fscanf(fp, "%s", number_str);
        int numero_de_bytes = atoi(number_str);


        if (!strncmp(command, "m", 1)){

            int B = insert(L1, L2, numero_de_bytes);

            // Si insert1() retorna la pos => se inserto exitosamente
            if(B > 0){                
                printf("Bloque de %d bytes asignado a partir del byte %d\n", numero_de_bytes, B);
            
            // Si insert1() retorna algo negativo => no hay espacio
            } else{
                printf("Bloque de %d bytes NO puede ser asignado\n", numero_de_bytes);
            }
        }else if(!strncmp(command, "f", 1)){
            
            freee();

            printf("Bloque de %d bytes liberado\n", numero_de_bytes);
        }
    }
    if(empty(L2))
        printf("Toda la memoria dinámica pedida fue liberada\n");
    else
        // TODO: todo
        printf("Quedaron N bloques sin liberar (B bytes) \n");

    return 0;
}