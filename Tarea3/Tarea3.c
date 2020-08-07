#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.c"
#include "heap.c"


int getPos(int codigo, util* arr, int len){
    for(int i = 0; i < len; i++){
        if(arr[i].codigo == codigo){
            return i;
        }
    }
    // Retorna -1 si no lo encontró
    return -1;
}


int main(int argc, char const *argv[]){


    // Calcular M

    int MProd, MOfer; // Tamaño de las tablas de hash
    int NProd, NOfer; // Cantidad de structs en archivos
    
    FILE *fp_prod;
    FILE *fp_ofer;

    // Crear y llenar la tabla de hash de los productos -----------------------------------------------
    fp_prod = fopen("productos.dat", "rb");

    fread(&NProd, sizeof(int), 1, fp_prod);

    MProd = (int) (NProd * 10.0 / 7 + 1);  // Ajusta el tamaño de la tabla para que sea α <= 0,7
    HTProd HT_Prod[MProd];

    for (int i = 1; i <= NProd; i++){
        producto p;
        fread(&p, sizeof(producto), 1, fp_prod);
        hashInsertProd(HT_Prod, p.codigo_producto, p, MProd);
    }
    fclose(fp_prod);

    // Crear y llenar la tabla de hash de las ofertas -----------------------------------------------
    fp_ofer = fopen("ofertas.dat", "rb");

    fread(&NOfer, sizeof(int), 1, fp_ofer);

    MOfer = (int) (NOfer * 10.0 / 7 + 1);  // Ajusta el tamaño de la tabla para que sea α <= 0,7
    HTOfer HT_Ofer[MOfer];

    for (int i = 1; i <= NOfer; i++){
        oferta o;
        fread(&o, sizeof(oferta), 1, fp_ofer);
        hashInsertOfer(HT_Ofer, o.codigo_producto, o, MOfer);
    }
    fclose(fp_ofer);


    // Abrir archivo compras.txt

    FILE *fp_compras;

    fp_compras = fopen("compras.txt", "r");

    int R, N;

    fscanf(fp_compras, "%d", &R);
    fscanf(fp_compras, "%d", &N);

    util arraySupremo[NProd];     // ---------------- TODO: Hacer de esta inutilidad el heap de una para asi echarnos unos 5 for
    int arraySupremo_len = 0;    //                          => eficiencia *= 2;

    for (int i = 1; i <= N; i++){
        int C;
        fscanf(fp_compras, "%d", &C);


        util arr[C];  

        int arr_len = 0;

        for (int j = 1; j < C; j++){
            int codigo_prod;
            fscanf(fp_compras, "%d", &codigo_prod);

            int pos = getPos(codigo_prod, arr, arr_len);
            if(pos == -1){
                // Si no lo encuentra se appendea al array
                arr[arr_len].codigo = codigo_prod;
                arr[arr_len].cantidad = 1; 
                arr_len++;
            } else{
                arr[pos].cantidad++; 
            }
        }

        // Tenemos un array con los codigos y cantidades de cada producto comprado -done
        // Ahora calculamos el total
        for(int j = 0; j < arr_len; j++){ // Para cada producto en el array
            int codigo, cantidad, cantidad_necesaria_para_que_se_aplique_la_oferta; // Nos quedamos sin nombres :c
            int veces_con_oferta;

            codigo = arr[j].codigo;
            cantidad = arr[j].cantidad;

            oferta o = hashSearchOfer(HT_Ofer, codigo, MOfer);
            producto p = hashSearchProd(HT_Prod, codigo, MProd);

            if(o.codigo_producto != VACIO && p.codigo_producto != VACIO)
                continue; // Se lo salta de pana si da error

            cantidad_necesaria_para_que_se_aplique_la_oferta = o.cantidad_descuento;

            veces_con_oferta = (cantidad / cantidad_necesaria_para_que_se_aplique_la_oferta);

            arr[j].total = cantidad * p.precio - veces_con_oferta * o.monto_descuento;
            strcpy(arr[j].nombre_producto, p.nombre_producto);     
        }

        // Agregar la info al array supremo
        for(int j = 0; j < arr_len; j++){
            int codigo = arr[j].codigo;
            int cantidad = arr[j].cantidad;
            int total = arr[j].total;

            int pos = getPos(codigo, arraySupremo, arraySupremo_len);

            if(pos == -1){
                // Si no lo encuentra se appendea al array
                arraySupremo[arraySupremo_len].codigo = codigo;
                arraySupremo[arraySupremo_len].cantidad = cantidad;
                arraySupremo[arraySupremo_len].total = total;  
                strcpy(arraySupremo[arraySupremo_len].nombre_producto, arr[j].nombre_producto);
                arraySupremo_len++;
            } else{
                arraySupremo[pos].cantidad += cantidad;
                arraySupremo[pos].total += total;
            }
        }
    }
    fclose(fp_compras);

    // Se insertan los datos en el heap
    heap h;
    heap_init(&h);
    for (int i = 0; i < arraySupremo_len; i++)
        heap_push(&h, arraySupremo[i]);

    heap_display(&h);   //DEBUG ---------------------------------------------------- BORRAR

    // Crear el archivo ranking.txt
    FILE *fp_ranking;

    fp_ranking = fopen("ranking.txt", "w");

    for (int i = 0; i < R; i++){
        util max = heap_getMax(&h);

        fprintf(fp_ranking, "%d %s %d %d\n", 
			   max.codigo, 
			   max.nombre_producto, 
			   max.cantidad, 
			   max.total
			);
    }
    fclose(fp_ranking);

    return 0;
}
