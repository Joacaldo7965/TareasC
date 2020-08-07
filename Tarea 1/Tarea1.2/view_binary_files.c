#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int nroCuenta;
    int saldo;
    char nbre[51];
    char direccion[51];
} clienteBanco;


/*****
*
void verArchivo( );
******
*
Imprime por pantalla la info de cada clienteBanco en el archivo.
******
*
Input:
*
char* f_name : Nombre del archivo a mostrar.
*
.......
******
*
Returns:
*
void, No retorna nada.
*****/
void viewFile(const char* f_name){

    FILE *fp;
    int cantidad_clientes = 0;
    clienteBanco clientee;

    fp = fopen( f_name, "r");

    if(fp == NULL){
        printf("Error al abrir el archivo.");
        exit(1);
    }
    while (fread(&clientee, sizeof(clienteBanco), 1, fp) == 1){
        cantidad_clientes++;
    }

    fseek(fp, 0, SEEK_SET);
    for (int i = 0; i < cantidad_clientes; i++){
        fread(&clientee, sizeof(clienteBanco), 1, fp);
        printf("--------------------------\n");
        printf("nroCuenta: %d\n", clientee.nroCuenta);
        printf("saldo: %d\n", clientee.saldo);
    }
    fclose(fp);
    return;
}

int main(int argc, char const *argv[]){
    viewFile(argv[1]);

    return 0;
}

