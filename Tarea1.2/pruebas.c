#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char* append(char* str, char c){
    int len = strlen(str);
    char *str2 = malloc(len + 1 + 1 ); /* one for extra char, one for trailing zero */
    strcpy(str2, str);
    str2[len] = c;
    str2[len + 1] = '\0';

    //printf( "%s\n", str2 ); /* prints "blablablaH" */
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
        char* str = "";
        char c_transaccion = 'x';

        while ((c_transaccion = getc(fpt)) != EOF){
            if(c_transaccion == 10)
                break;
            //str.append(c_transaccion);
            //strcat(str, c_transaccion);
            str = append(str, c_transaccion);
            
            printf( "String 2: %s\n", str);
            free(str);
            }
        if(c_transaccion == EOF)
            break;

        char *token = strtok(str, " "); 

        while (token != NULL) { 
            printf("token: [%s]\n", token); 
            token = strtok(NULL, " "); 
        }      
    }

    return 0;
}