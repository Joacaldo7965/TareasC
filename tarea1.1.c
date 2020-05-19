#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char ** buscar_str(char ** S, int n, char * P, int *tamArray_salidaa){
    int k = 0;
    
    //Largo de P
    int length_P = strlen(P);

    //Array
    char **salidaa;

    
    salidaa = malloc(sizeof(char) * n);

   for(int i = 0; i < n; i++){
       printf("comparación: %d\n", strncmp(P, S[i], length_P));
       printf("P: %s", P);
       printf("S[i]: %s", S[i]);
        if(strncmp(P, S[i], length_P) == 0){
            salidaa[k] = S[i];
            k++;
        }
   	}
    *tamArray_salidaa = k;

    return salidaa;
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

    fs = fopen("Archivo_S.txt", "r");
    fp = fopen("Archivo_P.txt", "r");

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
    char *array_S[largo_S];

    fseek(fs, 0, SEEK_SET);
	for(int i = 0; i < largo_S; i++){
        //printf("%d\n", i);
        fgets(palabra_in_S, sizeof(char) * 200, fs);
        printf("palabra_in_S: %s", palabra_in_S);
        array_S[i] = palabra_in_S;
        //printf("palabra_in_S: %s\n", palabra_in_S);
	}
    fclose(fs);
    for(int i = 0; i < largo_S; i++){
        printf("array_S%d: %s", i, array_S[i]);
	}

    fseek(fp, 0, SEEK_SET);

    int tamArray_prefijos;

    for(int j = 0; j < largo_P; j++){
        fgets(palabra_in_P, sizeof(palabra_in_P), fp);
        char **array_prefijos = buscar_str(array_S, largo_S, palabra_in_P, &tamArray_prefijos);

        printf("tamArray_prefijos: %d\n", tamArray_prefijos);

            /* Creación del archivo y todo el webeo del profe */
        
        //Puntero al archivo de salida
        FILE *fw;
        //Nombre del archivo de salida
        char f_out_name[204] = "";

        strcat(f_out_name, palabra_in_P);
        strcat(f_out_name, ".out");

        fw = fopen(f_out_name, "w");
        for(int i = 0; i < tamArray_prefijos; i++){
            printf("array_prefijos en %d: %s\n", i, array_prefijos[i]);
            fprintf(fw, "%s", array_prefijos[i]);
            }
        fclose(fw);
        }
    fclose(fp);
    }
