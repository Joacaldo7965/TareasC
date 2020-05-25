#include <stdio.h>
#include <stdlib.h>


typedef struct {
int nroCuenta;
int saldo;
char nbre[51];
char direccion[51];
} clienteBanco;

int main(int argc, char const *argv[]) {

  clienteBanco a;
  int r = 1;
  FILE *fp;
  fp = fopen("clientes.dat", "a");
  while (r < 10000000){
      a.nroCuenta = r;
      int random = rand() % 50000;
      printf("%d:\n",random);
      a.saldo = random;
      fwrite(&a,sizeof(clienteBanco),1,fp);
      r += 1;
  }
  fclose(fp);
  return 0;
}
