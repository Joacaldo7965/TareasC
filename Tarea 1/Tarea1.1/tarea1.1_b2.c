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
char** buscar_str();
******
*
Busca los Strings del arreglo S, tal que la palabra P es prefijo.
******
*
Input:
*
char** S : Arreglo S
int n    : Cantidad de Strings en el arreglo S
char* P  : Palabra P
long* tam_array_p : Parámetro de retorno, tamaño del arreglo que se retorna
*
.......
******
*
Returns:
*
char**, Array de Strings de S, tal que la palabra P es prefijo.
*****/
char** buscar_str(char** S, int n, char* P, long* tam_array_p){
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
    *tam_array_p = k;
    array_prefijos = realloc(array_prefijos, sizeof(char*) * k);
    return array_prefijos;
}

int main(int argc, char const *argv[]){
    long largo_p = 0, largo_s = 0;
    FILE *fps;
    FILE *fpp;
    char letra;

    // Abre el archivo S
    fps = fopen("S2.txt", "r");
    if(fps == NULL){
        printf("Error al abrir el archivo s.\n");
        exit(1);
    }

    // Calcula la cantidad de palabras en el archivo S
    for (letra = getc(fps); letra != EOF; letra = getc(fps))
        if(letra == '\n')
            largo_s++;

    // Crea un arreglo con las palabras en el archivo S
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

    // Abre el archivo P
    fpp = fopen("P.txt", "r");
    if(fpp == NULL){
        printf("Error al abrir el archivo p.\n");
        exit(1);
    }

    // Calcula la cantidad de palabras en el archivo P
    for (letra = getc(fpp); letra != EOF; letra = getc(fpp))
        if(letra == '\n')
            largo_p++;
        

    // Itera por las palabras P y llama a la funcion buscar_str()
    fseek(fpp, 0, SEEK_SET);
    for (int i = 0; i < largo_p; i++){
        char palabra[250] = "";
        long tam_array_prefijos;
        for (letra = getc(fpp); letra != EOF; letra = getc(fpp)){
            if(letra == '\n')
                break;
            char* str = append(palabra, letra);
            strcpy(palabra, str);
            free(str);
        }

        char** array_prefijos = buscar_str(array_s, largo_s, palabra, &tam_array_prefijos);

        //Puntero al archivo de salida
        FILE *fw;
        //Nombre del archivo de salida
        char f_out_name[250] = "";
        strcat(f_out_name, palabra);
        strcat(f_out_name, ".out");

        fw = fopen(f_out_name, "w");
        if(fw == NULL){
            printf("Error al generar el archivo %s", f_out_name);
            exit(1);
        }
        // Reescribe el archivo con las modificaciones.
        for (int i = 0; i < tam_array_prefijos; i++){
            fprintf(fw, "%s\n", array_prefijos[i]);
            free(array_prefijos[i]);    //Libera memoria utilizada para cada palabra
        }
        fclose(fw);
        free(array_prefijos);   //Libera memoria utilizada para el arreglo de palabras que son prefijos
    }

    for (int i = 0; i < largo_s; i++)
        free(array_s[i]);   //Libera memoria utilizada para cada palabra en el arreglo S
    free(array_s);
    return 0;
}


