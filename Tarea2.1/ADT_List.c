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



void initList(tLista *L) {
    L->head = L->tail = L->curr = malloc(sizeof(tNodo));
    L->listSize = 0; L->pos = 0;
    return;
}



void deleteAtPos(tLista *L, int position){ 
    tNodo *head = L->head;

    // If linked list is empty 
    if (head == NULL) 
        return; 
    // Store head node 
    tNodo* temp = head; 
  
    // If head needs to be removed 
    if (position == 0){ 
        head = temp->sig;   // Change head 
        free(temp);               // free old head 
        return; 
    } 
  
    // Find previous node of the node to be deleted 
    for (int i=0; temp!=NULL && i<position-1; i++) 
         temp = temp->sig; 
  
    // If position is more than number of nodes 
    if (temp == NULL || temp->sig == NULL) 
         return; 
  
    // Node temp->next is the node to be deleted 
    // Store pointer to the next of node to be deleted 
    tNodo *next = temp->sig->sig; 
  
    // Unlink the node from linked list 
    free(temp->sig);  // Free memory 
  
    temp->sig = next;  // Unlink the deleted node from list 
}


int insert(tLista* L1, tLista* L2, int bytes){//tElemLista start, tElemLista end) {

    // Recorre L1 Nodo a Nodo
    L1->curr = L1->head;
    L1->pos = 0;

    int flag = 0;

    int B;

    while (PRAVDA){
        if(L1->curr == NULL)
            return -1;

        int dif = L1->curr->end - L1->curr->start;

        if(dif > bytes){
            // Se quita de L1 el bloque pedido a partir del comienzo y se agrega el bloque quitado a L2
            /* El nodo de L1 queda:
                x->start = x->start + bytes + ¿1?;
                x->end = x->end;
                more info in "images/xd.png"
            */
            
            // Quitar bloque de L1 y reajustar lo restante
            B = L1->curr->start;
            L1->curr->start = B + bytes; //¿ + 1; ?

            // Agregar lo quitado de L1 a L2
            tNodo* aux = L2->curr->sig;
            L2->curr = L2->head;
            L2->curr->sig = malloc(sizeof(tNodo));
            L2->curr->sig->start = B;
            L2->curr->sig->end = B + bytes;
            L2->curr->sig->sig = aux;
            if (L2->curr == L2->tail) L2->tail = L2->curr->sig;
            L2->listSize++;

            return B;

        } else if(dif == bytes){
            // Si es igual se agrega tal cual a L2 y te lo pitiai de osico.

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
    


    /*
    tNodo* aux = L1->curr->sig;
    L1->curr->sig = malloc(sizeof(tNodo));
    L1->curr->sig->start = start;
    L1->curr->sig->end = end;
    L1->curr->sig->sig = aux;
    if (L1->curr == L1->tail) L1->tail = L1->curr->sig;
    L1->listSize++;

    return L1->pos;
    */
}

int insert2(tLista* L, tElemLista start, tElemLista end) {
    tNodo* aux = L->curr->sig;
    L->curr->sig = malloc(sizeof(tNodo));
    L->curr->sig->start = start;
    L->curr->sig->end = end;
    L->curr->sig->sig = aux;
    if (L->curr == L->tail) L->tail = L->curr->sig;
    L->listSize++;
    return L->pos;
}



void next(tLista* L) {
    if (L->curr != L->tail)
        L->curr = L->curr->sig; L->pos++;
}

// ¿¿ ??
void deleteHelp(tNodo** head) { 
   /* deref head to get the real head */
   tNodo* current = *head; 
   tNodo* next; 
  
   while (current != NULL){ 
       next = current->sig; 
       free(current); 
       current = next; 
   } 
    
   /* deref head to affect the real head back 
      in the caller. */
   *head = NULL; 
} 

void deleteList(tLista *L){
    return deleteHelp(&L->head);
}



void printHelp(tNodo* head) { 
    tNodo* temp = head;
    printf("List:\n"); 
    while (temp != NULL) { 
        printf("\tstart: %d\n", temp->start); 
        printf("\tend: %d\n", temp->end); 
        temp = temp->sig; 
    } 
}

void printList(tLista *L){
    return printHelp(L->head);
}