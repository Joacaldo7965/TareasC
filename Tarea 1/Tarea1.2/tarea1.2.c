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
char* append();
******
*
Agrega un char al final de un string.
******
*
Input:
*
char* str : String al que se le quiere agregar el char.
char c    : Char que se le agrega al String.
*
.......
******
*
Returns:
*
char*, Retorna un String extendido con un Char.
*****/
char* append(char* str, char c){
    int len = strlen(str);
    char *str2 = malloc(len + 2);
    strcpy(str2, str);
    str2[len] = c;
    str2[len + 1] = '\0';
    return str2;
}

/*****
*
void actualizarSaldos();
******
*
Revisa las Transacciones en transacciones.txt y modifica los datos de clientes.dat segun estas.
******
*
Input:
*
char* clientes      : Nombre del archivo binario donde están los datos de las cuentas bancarias.
char* transacciones : Nombre del archivo de texto donde están las transacciones a realizar.
*
.......
******
*
Returns:
*
void, No retorna nada.
*****/
void actualizarSaldos(char *clientes, char *transacciones){
    FILE *fpc;
    clienteBanco clientee;
    long cantidad_clientes = 0;

    fpc = fopen(clientes, "r");

    printf("abriendo archivo clientes: %s\n", clientes);

    if(fpc == NULL){
        exit(1);
    }

    while (fread(&clientee, sizeof(clienteBanco), 1, fpc) != 0){
        cantidad_clientes++;
        printf("%li\n", cantidad_clientes);
    }
    printf("Se terminó de contar los clientes\n");
    printf("cantidad de clientes: %li\n", cantidad_clientes);
    
    // Array de structs clientes
    clienteBanco* a_clientes;
    a_clientes = (clienteBanco*) malloc(sizeof(clienteBanco) * cantidad_clientes);
    printf("Array generado con tamaño %li\n", cantidad_clientes);

    fseek(fpc, 0, SEEK_SET);
    for (long i = 0; i < cantidad_clientes; i++){
        fread(&clientee, sizeof(clienteBanco), 1, fpc);
        a_clientes[i] = clientee;
    }
    fclose(fpc);

    // Transacciones
    FILE *fpt;

    fpt = fopen(transacciones, "r");
    printf("abriendo archivo transacciones: %s\n", transacciones);
    if(fpt == NULL){
        printf("Error al abrir el archivo %s", transacciones);
        exit(1);
    }

    while (1){  
        char str[50] = "";
        char c_transaccion = 'x';
        char* tokens[5];
        int t_count = 0;

        while ((c_transaccion = getc(fpt)) != EOF){
            if(c_transaccion == 10)
                break;
            char* str2 = append(str, c_transaccion);
            
            strcpy(str, str2);
            free(str2);
            }
        
        printf( "-------------\nString 2: %s\n", str);

        char *token = strtok(str, " "); 
        tokens[t_count] = token;

        while (token != NULL) { 
            token = strtok(NULL, " ");
            tokens[++t_count] = token; 
        }

        if(strcmp(tokens[0], "+") == 0 || strcmp(tokens[0], "-") == 0){
            // Deposita o substrae el dinero en la cuenta
            int existe = 0;

            char* s_sign = append(tokens[0], '1');
            int i_sign = (int) strtol(s_sign, NULL, 10);
            free(s_sign);

            int n_cliente = (int) strtol(tokens[1], NULL, 10);

            int deposito_cliente = ((int) strtol(tokens[2], NULL, 10)) * i_sign;

            for (long i = 0; i < cantidad_clientes; i++){
                if (a_clientes[i].nroCuenta == n_cliente){
                    a_clientes[i].saldo += deposito_cliente;
                    printf("nuevo saldo: %d\n", a_clientes[i].saldo);
                    existe = 1;
                    break;
                }
            }
            if(!existe){
                printf("El cliente '%d' no existe.\n", n_cliente);
                exit(1);
            } 
        } else if(strcmp(tokens[0], ">") == 0){
            // transfiere el dinero de la cuenta 1 a la cuenta 2
            int existe_c1 = 0, existe_c2 = 0;
            long a_index_1, a_index_2;

            int n_cliente_1 = (int) strtol(tokens[1], NULL, 10);
            int n_cliente_2 = (int) strtol(tokens[2], NULL, 10);

            int transferencia = (int) strtol(tokens[3], NULL, 10);

            // Revisa si existe la cuenta 1 y obtiene su índice en el array de clientes
            for (long i = 0; i < cantidad_clientes; i++){
                if (a_clientes[i].nroCuenta == n_cliente_1){
                    a_index_1 = i;
                    existe_c1 = 1;
                    break;
                }
            }
            // Revisa si existe la cuenta 2 y obtiene su índice en el array de clientes
            for (long i = 0; i < cantidad_clientes; i++){
                if (a_clientes[i].nroCuenta == n_cliente_2){
                    a_index_2 = i;
                    existe_c2 = 1;
                    break;
                }
            }
            if(existe_c1 && existe_c2){
                a_clientes[a_index_1].saldo -= transferencia;
                a_clientes[a_index_2].saldo += transferencia;
            } else if(existe_c2){
                printf("La cuenta '%d' no existe.\n", n_cliente_1);
                exit(1);
            } else{
                printf("La cuenta '%d' no existe.\n", n_cliente_2);
                exit(1);
            }   
        } else{
            printf("Operación no válida.");
            exit(1);
        }
        if(c_transaccion == EOF)
            break;
    }
    fclose(fpt);

    // Modificar archivo por los cambios

    FILE *fpw;

    fpw = fopen(clientes, "w");
    
    for (int i = 0; i < cantidad_clientes; i++){
        fwrite(&a_clientes[i], sizeof(clienteBanco), 1, fpw);
    }
    free(a_clientes);
    fclose(fpw);

    return;
}

int main(int argc, char *argv[]){
    printf("argc: %d\n", argc);
    if(argc < 2){
        printf("faltan argumentos\n");
    } else if (argc > 3){
        printf("sobran argumentos\n");
    } else{
        actualizarSaldos(argv[1], argv[2]);
    }
    return 0;
}
