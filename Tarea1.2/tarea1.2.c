#include <stdio.h>
#include <string.h>

typedef struct {
int nroCuenta;
int saldo;
char nbre[51];
char direccion[51];
} clienteBanco;

/*****
*
void actualizarSaldos
******
*
actualiza los saldos xdxdxdxd
******
*
Input:
*
tipoParámetro NombreParámetro : Descripción Parámetro
*
.......
******
*
Returns:
*
TipoRetorno, Descripción retorno
*****/
void actualizarSaldos(char *clientes, char *transacciones){
    FILE *fpc;
    clienteBanco clientee;
    int cantidad_clientes = 0;

    fpc = fopen(clientes, "r");

    if(fpc == NULL){
        exit(1);
    }

    while (fread(&clientee, sizeof(clienteBanco), 1, fpc) == 1){
        cantidad_clientes++;
    }
    
    clienteBanco a_clientes[cantidad_clientes];

    fseek(fpc, 0, SEEK_SET);
    for (int i = 0; i < cantidad_clientes; i++){
        fread(&clientee, sizeof(clienteBanco), 1, fpc);
        a_clientes[i] = clientee;
    }
    fclose(fpc);

    // Transacciones
    FILE *fpt;
    char c_transaccion;
    int count = 0;

    fpt = fopen(transacciones, "r");
    
    if(fpt == NULL){
        exit(1);
    }
    while (1){  
        char* str = "";
        while ((c_transaccion = getc(fpt)) != EOF){
            if(c_transaccion == 10)
                break;
            //str.append(c_transaccion);
            strcat(str, c_transaccion);
            }
        char *token = strtok(str, " "); 

        while (token != NULL) { 
            printf("%s\n", token); 
            token = strtok(NULL, " "); 
        }     
        break;  
    }
}

int main(int argc, char *argv[]){
    if(argc < 2){
        printf("falta argumentos\n");
    } else if (argc > 3){
        printf("sobran argumentos\n");
    } else{
        actualizarSaldos(argv[0], argv[1]);
    }
    
    
    return 0;
}