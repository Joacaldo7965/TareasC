#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char* append(char* str, char c){
    int len = strlen(str);
    char *str2 = malloc(len + 1 + 1 );
    strcpy(str2, str);
    str2[len] = c;
    str2[len + 1] = '\0';
    return str2;
}

int main(){
    char *transacciones = "ejemplo.txt";

    // Transacciones
    FILE *fpt;

    fpt = fopen(transacciones, "r");
    
    if(fpt == NULL){
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
            //str.append(c_transaccion);
            //strcat(str, c_transaccion);
            char* str2 = append(str, c_transaccion);
            
            strcpy(str, str2);
            free(str2);
            }
        printf( "String 2: %s\n", str);

        char *token = strtok(str, " "); 
        tokens[t_count] = token;

        while (token != NULL) { 
            token = strtok(NULL, " ");
            tokens[++t_count] = token; 
        }
        for (int i = 0; i < t_count; i++){
            printf("token: [%s]\n", tokens[i]); 
        }


        //TODO TODO
        // ver que funcion es (+ - >)
            /*code*/
        // realizar la accion en el array a_clientes
            /*code*/
        // modificar el archivo binario con los cambios
            /*code*/


        if(c_transaccion == EOF)
            break;
    }

    return 0;
}