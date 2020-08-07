#include "ADT_BST.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*****
*
int sucesor()
******
*
Retorna el menor valor, de los mayores a n. 
Si no lo encuentra retorna u.
******
*
Input:
*
Node* T : Raíz del árbol.
int   n : El numero del que se quiere saber el sucesor.
int   u : El máximo valor posible del árbol.
*
.......
******
*
Returns:
*
int, Retorna el menor valor, de los mayores a n.
*****/
int sucesor(Node* T, int n, int u){
    // Recorrido In-orden
    int mejor = u;

    /*****
    *
    int inOrden()
    ******
    *
    Recorre el árbol en inOrden buscando el sucesor.
    ******
    *
    Input:
    *
    Node* T : Raíz del árbol.
    *
    .......
    ******
    *
    Returns:
    *
    int, Retorna el sucesor.
    *****/   
    int inOrden(Node* Node){
        int pasocorbata = 1;
        if(Node != NULL){
            inOrden(getLeft(Node));
            int dif = getValue(Node) - n;
            if(dif > 0){
                if(dif < mejor)
                    mejor = dif;
                else
                    pasocorbata = 0;
            }
            if (pasocorbata)
                inOrden(getRight(Node));
        }
        if(mejor == u) return u;
        return mejor + n;
    }

    return inOrden(T);
}



int main(int argc, char const *argv[]){


    FILE *fp;
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
    Node *T = initTree();
    
    while (!feof(fp)){
        fscanf(fp,"%s",command);
        
        //printf("command: %s\n", command);

        if (!strncmp(command, "P", 1)){
            preOrden(T);
            printf("\n");
        }else{

            fscanf(fp, "%s", number_str);
            int number = atoi(number_str);

            if(!strncmp(command, "S", 1)){
                int s = sucesor(T, number, u);
                printf("%d\n", s); 
            } else if (!strncmp(command, "I", 1)){
                T = insert(T, number);
            } else if (!strncmp(command, "B", 1)){
                remove_(T, number);
            }
        }
    }
    
    fclose(fp);

    return 0;
}
