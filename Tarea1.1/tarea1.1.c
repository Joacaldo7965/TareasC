#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char ** buscar_str(char ** S, int n, char * P, int *tamArray_salidaa){
    int k = 0;
    
    //Largo de P
    int length_P = strlen(P) - 1;

    //Array
    char **salidaa;

    
    salidaa = malloc(sizeof(char) * n);
    if(salidaa == NULL)
        printf("Error al hacer el\n");
    //printf("lengt_P: %d\n", length_P);
    for(int i = 0; i < n; i++){
        //printf("P: %s", P);
        //printf("S[i]: %s", S[i]);
        //printf("comparación: %d\n", strncmp(P, S[i], length_P));
        if(strncmp(P, S[i], length_P) == 0){
            salidaa[k] = S[i];
            k++;
        }
   	}
    *tamArray_salidaa = k;

    return salidaa;
}

void remove_spaces(char* s) {
    const char* d = s;
    do {
        while (*d == '\n') {
            ++d;
        }
    } while (*s++ = *d++);
}

int main(){
	
    FILE *fs, *fp;
    int largo_S = 0, largo_P = 0;

    //Char en ASCII
    int letra;

    //Palabra (string)
    char palabra_in_S[200];
    
    //Hay que cambiar esta wea
    //Palabra en P (string)
    char palabra_in_P[200];

    fs = fopen("S2.txt", "r");
    fp = fopen("P.txt", "r");

    //saber cuantos strings hay en Archivo_S (n)
    if (fs) {
        while ((letra = getc(fs)) != EOF){
            if(letra == 10)
                largo_S++;
        }    
    }
    //printf("Hay %d strings en el archivo s.\n", largo_S);

    if (fp) {
        while ((letra = getc(fp)) != EOF)
            if(letra == 10)
                largo_P++;
    }

    //Array de S
    char* array_S[largo_S];

    fseek(fs, 0, SEEK_SET);
	for(int i = 0; i < largo_S; i++){
        //printf("%d\n", i);
        fgets(palabra_in_S, sizeof(char) * 200, fs);
        //printf("palabra_in_S: %s", palabra_in_S);
        
            /* TODO */         
        // esta wea no sirve, hay que arreglarlo xdxd
        //array_S[i] = palabra_in_S;
        array_S[i] = malloc(sizeof(char)*200);
        strcpy(array_S[i], palabra_in_S);
        //free(array_S[i]);

	}
    fclose(fs);

    fseek(fp, 0, SEEK_SET);

    int tamArray_prefijos;

    for(int j = 0; j < largo_P; j++){
        fgets(palabra_in_P, sizeof(palabra_in_P), fp);
        char **array_prefijos = buscar_str(array_S, largo_S, palabra_in_P, &tamArray_prefijos);

        //printf("tamArray_prefijos: %d\n", tamArray_prefijos);

            /* Creación del archivo y todo el webeo del profe */
        
        //Puntero al archivo de salida
        FILE *fw;
        //Nombre del archivo de salida
        char f_out_name[204] = "";


        remove_spaces(palabra_in_P);

        strcat(f_out_name, palabra_in_P);
        strcat(f_out_name, ".out");

        fw = fopen(f_out_name, "w");
        if(!fw){
            exit(1);
        }
        printf("tamArray: %d\n", tamArray_prefijos);

        for(int i = 0; i < tamArray_prefijos; i++){

            /* esta linea esta como las weas*/
            //fprintf(fw, "%s", array_prefijos[i]);

            printf("array_prefijos[%d]: %s\n", i, array_prefijos[i]);
            }
        fclose(fw);

        }
    fclose(fp);

    return 0;
    } 