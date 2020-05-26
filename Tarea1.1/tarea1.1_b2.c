#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    char *str2 = malloc(len + 3);
    strcpy(str2, str);
    str2[len] = c;
    str2[len + 1] = '\0';
    return str2;
}

/*****
*
void remover_espacios();
******
*
Remueve los 
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
void remover_espacios(char* s) {
    const char* d = s;
    do {
        while (*d == '\n')
            ++d;
    } while ((*s++ = *d++));
}

char** buscar_str(char** S, int n, char* P, long* tam_array_prefijos){
    char** array_prefijos =  malloc(sizeof(char*) * n);
    
    int length_P = strlen(P);

    long k = 0;
    for (int i = 0; i < n; i++){
        if(strncmp(P, S[i], length_P) == 0){
            array_prefijos[k] = malloc(sizeof(char) * 250);
            strcpy(array_prefijos[k], S[i]);
            k++;
        }
    }
    *tam_array_prefijos = k;
    array_prefijos = realloc(array_prefijos, sizeof(char*) * k);
    return array_prefijos;
}

int main(int argc, char const *argv[]){
    long largo_p = 0, largo_s = 0;
    FILE *fps;
    FILE *fpp;
    char letra;

    fps = fopen("S2.txt", "r");
    if(fps == NULL){
        printf("Error al abrir el archivo s.\n");
        exit(1);
    }

    fpp = fopen("P.txt", "r");
    if(fpp == NULL){
        printf("Error al abrir el archivo p.\n");
        exit(1);
    }

    for (letra = getc(fps); letra != EOF; letra = getc(fps))
        if(letra == '\n')
            largo_s++;

    for (letra = getc(fpp); letra != EOF; letra = getc(fpp))
        if(letra == '\n')
            largo_p++;

    char* array_s[largo_s];
    fseek(fps, 0, SEEK_SET);
    for (long i = 0; i < largo_s; i++){
        char palabra[250] = "";
        int k = 0;
        for (letra = getc(fps); letra != EOF; letra = getc(fps)){
            if(letra == '\n')
                break;
            char* str = append(palabra, letra);
            strcpy(palabra, str);
            free(str);
            k++;
        }
        array_s[i] = (char*) malloc(sizeof(char) * k + 1);
        strcpy(array_s[i], palabra);
    }

    fseek(fpp, 0, SEEK_SET);
    for (int i = 0; i < largo_p; i++){
        char palabra[250] = "";
        int k = 0;
        long tam_array_prefijos;
        for (letra = getc(fpp); letra != EOF; letra = getc(fpp)){
            if(letra == '\n')
                break;
            char* str = append(palabra, letra);
            strcpy(palabra, str);
            free(str);
            k++;
        }

        char** array_prefijos = buscar_str(array_s, largo_s, palabra, &tam_array_prefijos);

        //Puntero al archivo de salida
        FILE *fw;
        //Nombre del archivo de salida
        char f_out_name[250] = "";

        //remover_espacios(palabra);
        strcat(f_out_name, palabra);
        strcat(f_out_name, ".out");

        fw = fopen(f_out_name, "w");
        if(!fw){
            printf("Error al generar el archivo %s", f_out_name);
            exit(1);
        }
        for (int i = 0; i < tam_array_prefijos; i++){
            fprintf(fw, "%s\n", array_prefijos[i]);
            //printf("array: %s\n", array_prefijos[i]);
            free(array_prefijos[i]);
        }
        fclose(fw);
        free(array_prefijos);   
    }
    for (int i = 0; i < largo_s; i++)
        free(array_s[i]);   
    return 0;
}


