#include "ADT_BST.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int sucesor(Node* T, int n, int u){
    // Recorrido In-orden
    int mejor = u;
    int pasocorbata;
    Node* nodeRight;
    Node* nodeLeft;
    int nodeValue;
    int dif;

    int inOrden(Node* T){
        // Algoritmo de Tomás Dijkstra
        pasocorbata = 1;
        if(T == NULL) return u;
        nodeRight = getRight(T);
        nodeLeft = getLeft(T);
        inOrden(nodeLeft);
        nodeValue = getValue(T);
        dif = nodeValue - n;
        //printf("dif: %d\n", dif);
        if(dif > 0)
            if(dif < mejor)
                mejor = dif;
            else
                pasocorbata = 0;
        if (pasocorbata)
            inOrden(nodeRight);
        if(mejor == u) return u;
        return mejor + n;
    }

    return inOrden(T);
}

int main(int argc, char const *argv[]){

    FILE *fp;
    char ch;
    long u;

    fp = fopen("input.txt", "r");
    if (fp == NULL){
        printf("Error al abrir el archivo.\n");
        exit(1);
    }

    // get u
    fscanf(fp,"%ld",&u);

    char command[9];
    char number_str[9];

    // Init Tree
    Node *T = initTree(T);
    
    while (!feof(fp)){
        fscanf(fp,"%s",command);
        
        if (!strncmp(command, "P", 1)){
            preOrden(T);
            //printf("\n");
        }else{

            fscanf(fp, "%s", number_str);
            int number = atoi(number_str);

            if(!strncmp(command, "S", 1)){
                sucesor(T, number, u);
                //printf("%d\n", sucesor(T, number, u)); 
            } else if (!strncmp(command, "I", 1)){
                T = insert(T, number);
            } else if (!strncmp(command, "B", 1)){
                remove_(T, number);
            }
        }
    }
    //clear(T);
    
    fclose(fp);

    return 0;
}
