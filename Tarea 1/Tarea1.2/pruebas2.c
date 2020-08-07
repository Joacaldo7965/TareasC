#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* append(char* str, char c){
    int len = strlen(str);
    char *str2 = malloc(len + 1 + 1 );
    strcpy(str2, str);
    str2[len] = c;
    str2[len + 1] = '\0';
    return str2;
}

int main(int argc, char const *argv[]){
    char* tokens[5];
    tokens[0] = "-";
    tokens[1] = "456";
    char* s_sign = append(tokens[0], '1');
    int i_sign = (int) strtol(s_sign, NULL, 10);
    printf("%d\n", i_sign);
    free(s_sign);
    int n_cliente = (int) strtol(tokens[1], NULL, 10);
    printf("%d\n", n_cliente+1);
    return 0;
}
