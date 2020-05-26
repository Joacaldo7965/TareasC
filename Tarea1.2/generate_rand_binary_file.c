#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    int nroCuenta;
    int saldo;
    char nbre[51];
    char direccion[51];
} clienteBanco;

/*****
*
void generateFile();
******
*
Genera un archivo 'clientes.dat' con structs clienteBanco con saldos aleatorios.
******
*
Input:
*
int cantidad_clientes : Cantidad de clientes con la que se quiere generar el archivo.
*
.......
******
*
Returns:
*
void, No retorna nada.
*****/
void generateFile(int cantidad_clientes){
    FILE *fp;
    clienteBanco a;
    int r = 1;

    char* direccionn = "direccion_ejemplo";
    char* nbree = "nombre_ejemplo";

    strcpy(a.direccion, direccionn);
    strcpy(a.nbre, nbree);
    fp = fopen("clientes.dat", "w");
    while (r < cantidad_clientes){
        a.nroCuenta = r;
        int random = rand() % 50000;
        printf("%d:\n",random);
        a.saldo = random;      
        fwrite(&a,sizeof(clienteBanco),1,fp);
        r += 1;
    }
    fclose(fp);
    return;
}

int main(int argc, char const *argv[]) {
    int n = (int) strtol(argv[1], NULL, 10);
    generateFile(n);
    return 0;
}
