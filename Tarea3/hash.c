#include <stdio.h>

#define VACIO -1
#define VALORINVALIDO -2

typedef struct{
    int codigo_producto;
    char nombre_producto[31];
    int precio;
} producto;

typedef struct {
    int codigo_producto;
    int cantidad_descuento; //Indica la cantidad exacta de unidades (del producto en cuestión) que deben comprarse para aplicar el descuento.
    int monto_descuento;    // Indica la cantidad de pesos a descontar en total
} oferta;

/* --- Hashing --- */
typedef struct {
    int clave;
    producto info;
} HTProd;

typedef struct {
    int clave;
    oferta info;
} HTOfer;


unsigned int h(unsigned int x, int M) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x % M;
}

int h2(int x, int M){
    return x % M;
}

int p(int k, int i, int M){
    return i * h2(k, M);
}



int hashInsertProd(HTProd HT[], int k, producto prod, int M) {
    int inicio, i;
    int pos = inicio = h(k, M);
    for (i = 1; HT[pos].clave != VACIO && HT[pos].clave != k; i++)
        pos = (inicio + p(k, i, M)) % M; // próxima ranura en la secuencia
    if (HT[pos].clave == k)
        return 0; // inserción no exitosa: clave repetida
    else {
        HT[pos].clave = k;
        HT[pos].info = prod;
        return 1; // inserción exitosa
    }
}

int hashInsertOfer(HTOfer HT[], int k, oferta ofer, int M) {
    int inicio, i;
    int pos = inicio = h(k, M);
    for (i = 1; HT[pos].clave != VACIO && HT[pos].clave != k; i++)
        pos = (inicio + p(k, i, M)) % M; // próxima ranura en la secuencia
    if (HT[pos].clave == k)
        return 0; // inserción no exitosa: clave repetida
    else {
        HT[pos].clave = k;
        HT[pos].info = ofer;
        return 1; // inserción exitosa
    }
}

producto hashSearchProd(HTProd HT[], int k, int M) {
    int inicio, i;
    int pos = inicio = h(k, M);
    for (i = 1; HT[pos].clave != VACIO && HT[pos].clave != k; i++)
        pos = (inicio + p(k, i, M)) % M; // próxima ranura en la secuencia

    if (HT[pos].clave == k)
        return HT[pos].info; // registro encontrado, búsqueda exitosa
    producto p_nulo;
    p_nulo.codigo_producto = VACIO;
    return p_nulo;
}

oferta hashSearchOfer(HTOfer HT[], int k, int M) {
    int inicio, i;
    int pos = inicio = h(k, M);
    for (i = 1; HT[pos].clave != VACIO && HT[pos].clave != k; i++)
        pos = (inicio + p(k, i, M)) % M; // próxima ranura en la secuencia

    if (HT[pos].clave == k)
        return HT[pos].info; // registro encontrado, búsqueda exitosa
    
    oferta o_nulo;
    o_nulo.codigo_producto = VACIO;
    return o_nulo;
}


/*------------------------*/