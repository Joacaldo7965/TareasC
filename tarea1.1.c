#include <stdio.h>
#include <stdlib.h>

/*
char ** buscar_str(char ** S, int n, char * P){

    //for letra(linea) in archivo
    for(int i = 0;i < n; i++){

   	}
    return;
}
*/

int main(){
	
    FILE *fs, *fp;
    int largo_S = 0, largo_P = 0;
    //Char en ASCII
    int letra;
    //Palabra (string)
    char palabra[200];

    fs = fopen("Archivo_S.txt", "r");
    fp = fopen("Archivo_P.txt", "r");

    //saber cuantos strings hay en Archivo_S (n)
    if (fs) {
        while ((letra = getc(fs)) != EOF){
            if(letra == 10)
                largo_S++;
        }    
    }
    printf("Hay %d strings en el archivo s.\n", largo_S);

    if (fp) {
        while ((letra = getc(fp)) != EOF)
            if(letra == 10)
                largo_P++;
    }

    //Array de S
    char* array_S[largo_S];

    fseek(fs,0,SEEK_SET);
	for(int i = 0; i < largo_S; i++){
        printf("%d\n", i);
        fgets(palabra, sizeof(palabra), fs);
        array_S[i] = palabra;
        printf("palabra: %s\n", palabra);
	}

    fclose(fp);
    fclose(fs);
}