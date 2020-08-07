#include <stdio.h>
#include <stdlib.h>
//#define правдa 1
#define PRAVDA 1

typedef int tElemLista;

typedef struct nodo {
    tElemLista start;
    tElemLista end;
    struct nodo* sig;
} tNodo;

typedef struct {
    tNodo* head;
    tNodo* tail;
    tNodo* curr;
    unsigned int listSize;
    unsigned int pos;
} tLista;


/*****
*
void initLista()
******
*
Inicializa la lista.
******
*
Input:
*
tLista* L : Lista a inicializar.
*
.......
******
*
Returns:
*
void, No retorna nada.
*****/
void initList(tLista *L) {
    L->head = L->tail = L->curr = malloc(sizeof(tNodo));
    L->listSize = 0; L->pos = 0;
    return;
}


/*****
*
void deleteAtPos()
******
*
Borra un elemento de la lista en cierta posicion.
******
*
Input:
*
tLista* L : Lista.
int position: Posicion del elemente a borrar.
*
.......
******
*
Returns:
*
void, No retorna nada.
*****/
void deleteAtPos(tLista *L, int position){ 
    tNodo *head = L->head;

    // Si la lista esta vacia
    if (head == NULL) 
        return; 
    // Guarda el Head
    tNodo* temp = head; 
  
    // Si el head necesita ser eliminado 
    if (position == 0){ 
        head = temp->sig;   // Se cambia el head
        free(temp);               // Libera la head antigua 
        return; 
    } 
  
    // Se busca el nodo anterior al que se quiere eliminar
    for (int i=0; temp!=NULL && i<position-1; i++) 
         temp = temp->sig; 
  
    // Si la posicion es mayor a la cantidad de nodos
    if (temp == NULL || temp->sig == NULL) 
         return; 
  
    // temp->sig es el que se quiere borrar
    // Se guarda el siguiente al que se quiere borrar
    tNodo *next = temp->sig->sig; 
  
    // Se elimina el nodo
    free(temp->sig);
    temp->sig = next;  // Se ajustan los punteros
}

/*****
*
int mallok()
******
*
Busca el espacio pedido en L1 y lo agrega a L2.
******
*
Input:
*
tLista* L1    : Lista 1.
tLista* L2    : Lista 2.
int     bytes : bytes que fueron pedidos.
*
.......
******
*
Returns:
*
int, Retorna el byte donde fue asignada la memoria.
*****/
int mallok(tLista* L1, tLista* L2, int bytes){

    // Recorre L1 Nodo a Nodo
    L1->curr = L1->head;
    L1->pos = 0;

    int B;

    while (PRAVDA){
        if(L1->curr == NULL)
            return -1;

        // Tamaño del nodo
        int dif = L1->curr->end - L1->curr->start + 1;

        if(dif > bytes){
            // Se quita de L1 el bloque pedido a partir del comienzo y se agrega el bloque quitado a L2
            /* El nodo de L1 queda:
            *    x->start = x->start + bytes;
            *    x->end = x->end;
            */
            
            // Quitar bloque de L1 y reajustar lo restante
            B = L1->curr->start;
            L1->curr->start = B + bytes;

            // Agregar lo quitado de L1 a L2
            L2->curr = L2->head;
            tNodo* aux = L2->curr->sig;
            L2->curr->sig = malloc(sizeof(tNodo));
            L2->curr->sig->start = B;
            L2->curr->sig->end = B + bytes;
            L2->curr->sig->sig = aux;
            if (L2->curr == L2->tail) L2->tail = L2->curr->sig;
            L2->listSize++;

            return B;

        } else if(dif == bytes){
            // Si es igual se agrega tal cual a L2 y se elimina.

            B = L1->curr->start;

            tNodo* aux = L2->curr->sig;
            L2->curr = L2->head;
            L2->curr->sig = malloc(sizeof(tNodo));
            L2->curr->sig->start = B;     // Mismo start
            L2->curr->sig->end = L1->curr->end;         // Mismo end
            L2->curr->sig->sig = aux;
            if (L2->curr == L2->tail) L2->tail = L2->curr->sig;
            L2->listSize++;

            deleteAtPos(L1, L1->pos);

            return B;
        }
        // Si no sucede ninguna de los anteriores se sigue buscando espacio en el siguiente de la lista
        // y se cumple el primer if el cual retorna un valor negativo.
        L1->curr = L1->curr->sig;
        L1->pos++;
    }
}

/*****
*
int insert()
******
*
Inserta un elemento en la lista
******
*
Input:
*
tLista*    L     : Lista donde se insertan los elementos.
tElemLista start : Primer elemento a insertar.
tElemLista end   : Segundo elemento a insertar.
*
.......
******
*
Returns:
*
int, Retorna la posicion en la que fueron insertados los elementos.
*****/
int insert(tLista *L, tElemLista start, tElemLista end) {
    tNodo* aux = L->curr->sig;
    L->curr->sig = malloc(sizeof(tNodo));
    L->curr->sig->start = start;
    L->curr->sig->end = end;
    L->curr->sig->sig = aux;
    if (L->curr == L->tail) L->tail = L->curr->sig;
    L->listSize++;
    return L->pos;
}

/*****
*
int freee()
******
*
Busca el byte inicial del bloque que se quiere liberar en L2 y lo pone en el espacio libre L1.
******
*
Input:
*
tLista* L1 : Lista 1.
tLista* L2 : Lista 2.
int bytes : Byte donde comienza el bloque que se desea liberar.
*
.......
******
*
Returns:
*
int, Retorna los bytes que fueron liberados.
*****/
int freee(tLista *L1, tLista *L2, int bytes){
    /* Se busca en L2 hasta que L2->curr->start sea igual a bytes.
    *  Luego se añade a L1 respetando el orden, despues:
    *   1) Se verifica si L1->curr->start == L1->prev->end:
    *           En tal caso se hace el merge entre el bloque prev y el curr
    *   2) Se verifica si L1->curr->end == L1->curr->sig->start:
    *           En tal caso se hace el merge de los bloques curr y curr->sig
    * 
    *   Finalmente se borra el bloque de L2.
    */


    L2->curr = L2->head;
    L2->pos = 0;

    while (PRAVDA){

        // Si la lista esta vacía o en su defecto llego al final retorna;
        if(L2->curr == NULL)
            return -1;
        
        // Si se encontró el byte se hace el freee y se retorna
        if(L2->curr->start == bytes){
            
            /* 2 Opciones:
            *  1) Sorted Insert en L1 y luego hacer merge si se cumplen 
            *     las condiciones antes mencionadas
            * 
            *  2) Hacer el Sorted Insert directamente con el merge          <-------------
            */

            // Opción 2
            tNodo *new_node = malloc(sizeof(tNodo));

            new_node->start = L2->curr->start;
            new_node->end = L2->curr->end;

            // Cuando es head
            if (L1->head == NULL || L1->head->start >= new_node->start) { 
                /* 2 casos: 
                *   1) new_node->end != head->start
                *   2) new_node->end == head->start
                *
                *   __________
                *  |          |
                *  | new_node |
                *  |__________|
                *                 
                *       |
                *       v
                *             __________          _______________
                *            |          |        |               |
                *            |   head   |  ----> |  current->sig | ---->  ...
                *            |__________|        |_______________|
                */

                if(new_node->end != L1->head->start){
                    new_node->sig = L1->head; 
                    L1->head = new_node; 
                } else{
                    L1->head->start = new_node->start;  // Se extiende head con el new_node
                }        
            } 
            else { 
                tNodo *current = L1->head;
                
                // Se busca el nodo anterior a el que se quiere insertar
                while (current->sig != NULL && current->sig->start < new_node->start) { 
                    current = current->sig; 
                }

                // Ver los casos de merge
                /*               __________
                *               |          |
                *               | new_node |
                *               |__________|
                *                  
                *                    |
                *                    v
                *      __________          _______________
                *     |          |        |               |
                * --> | current  |  ----> |  current->sig | ---->  ...
                *     |__________|        |_______________|
                */

                if(current->sig == NULL){ // En el caso en que se añada el nodo en la cola
                    current->sig = new_node;
                }else if(current->end == new_node->start && new_node->end == current->sig->start){

                    current->end = current->sig->end;  // Se extiende con el nodo anterior y posterior
                    current->sig = current->sig->sig;  // Se modifican los punteros

                }else if(current->end == new_node->start){
                    current->end = new_node->end;  // Se extiende el nodo anterior y los punteros se mantienen

                }else if(new_node->end == current->sig->start){
                    current->sig->start = new_node->start; // Se extiende con el nodo posterior y los punteros se mantienen
                } else{
                    new_node->sig = current->sig; 
                    current->sig = new_node; 
                }
            } 
            
            int memoria_liberada = L2->curr->end - L2->curr->start;
            
            deleteAtPos(L2, L2->pos);

            return memoria_liberada;
        }     
        L2->curr = L2->curr->sig;
        L2->pos++;
    }
}


/*****
*
void sinLiberar()
******
*
Cuenta la cantidad de elementos de la lista y además cuantos bytes quedan sin liberar.
******
*
Input:
*
tLista* L         : Lista.
int*    b_no_lib  : referencia a bytes no liberados.
int*    n_bloques : referencia al numero de elementos de la lista
*
.......
******
*
Returns:
*
TipoRetorno, Descripción retorno
*****/
void sinLiberar(tLista *L, int *b_no_lib, int *n_bloques){
    L->curr = L->head;
    L->pos = 0;

    int dif;

    //printList(L);

    // Recorre todos los nodos
    while (PRAVDA){
        if(L->curr == NULL)
            return;

        // Cada nodo se suma los bytes no liberados
        dif = L->curr->end - L->curr->start;
        if (dif != 0){
            *b_no_lib += (dif);
            *n_bloques += 1;    
        }

        L->curr = L->curr->sig;
        L->pos++;
    }
    
}

/*****
*
void printList()
******
*
Hace un print de la lista. (usado para debug)
******
*
Input:
*
tLista* L : Lista a printear.
*
.......
******
*
Returns:
*
void, No retorna nada.
*****/
void printList(tLista *L){
    tNodo* temp = L->head;
    while (temp != NULL) { 
        printf("\tstart: %d\n", temp->start); 
        printf("\tend: %d\n", temp->end); 
        temp = temp->sig; 
    }
}

