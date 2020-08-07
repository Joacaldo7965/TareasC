#include "ADT_List.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char const *argv[]){

    FILE *fp;
    FILE *fw;
    long M;
    long N;

    fp = fopen("input1.dat", "r");
    if (fp == NULL){
        printf("Error al abrir el archivo.\n");
        exit(1);
    }
    
    fscanf(fp,"%ld",&M);
    fscanf(fp,"%ld",&N);


    // Init Lists
    tLista *L1 = malloc(sizeof(tLista));
    tLista *L2 = malloc(sizeof(tLista));

    initList(L1); insert(L1, 1, M); // init Lista 1 con nodo inicial
    
    initList(L2);                   // init Lista 2 vacia
    

    char command[7];
    char number_str[11];
    int numero_de_bytes;

    fw = fopen("output.dat", "w");
    if (fw == NULL){
        printf("Error al crear el archivo.\n");
        exit(1);
    }


    for (int i = 0; i < N; i++){
    
        fscanf(fp,"%s", command);
        fscanf(fp, "%s", number_str);
        numero_de_bytes = atoi(number_str);


        if (!strncmp(command, "m", 1)){

            int B = mallok(L1, L2, numero_de_bytes);

            // Si mallok() retorna la pos => se inserto exitosamente
            if(B > 0){                
                //printf("Bloque de %d bytes asignado a partir del byte %d\n", numero_de_bytes, B); // Debug
                fprintf(fw, "Bloque de %d bytes asignado a partir del byte %d\n", numero_de_bytes, B);
            
            // Si mallok() retorna algo negativo => no hay espacio
            } else{
                //printf("Bloque de %d bytes NO puede ser asignado\n", numero_de_bytes);  // Debug
                fprintf(fw, "Bloque de %d bytes NO puede ser asignado\n", numero_de_bytes);
            }
        }else if(!strncmp(command, "f", 1)){
            
            int mem_liberada = freee(L1, L2, numero_de_bytes);

            //printf("Bloque de %d bytes liberado\n", mem_liberada);    // Debug
            fprintf(fw, "Bloque de %d bytes liberado\n", mem_liberada);
        }

        // For debbug
        /*
        printf("L1:\n");
        printList(L1);
        printf("L2:\n");
        printList(L2);
        */
        
        
    }

    int b_no_liberados = 0;
    int n_bloques = 0;

    sinLiberar(L2, &b_no_liberados, &n_bloques);

    if(n_bloques == 0){
        //printf("Toda la memoria dinámica pedida fue liberada\n"); // Debug
        fprintf(fw, "Toda la memoria dinámica pedida fue liberada\n");
    }
    else{
        //printf("Quedaron %d bloques sin liberar (%d bytes) \n", n_bloques, b_no_liberados); // Debug
        fprintf(fw, "Quedaron %d bloques sin liberar (%d bytes) \n", n_bloques, b_no_liberados);
    }

    fclose(fp);
    fclose(fw);
    return 0;
}