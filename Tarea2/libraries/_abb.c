//bynary search tree
#include <stdio.h>
#include <stdlib.h>

typedef struct nodoArbolBin{
  int info;
  struct nodoArbolBin *izq;
  struct nodoArbolBin *der;
} tNodoArbolBin;

typedef struct{
  tNodoArbolBin *raiz;
  int nElems;
} tABB;


//funcion auxiliar de clear()
void clearHelp(tNodoArbolBin *nodo){
  if(nodo == NULL) return;
  clearHelp(nodo->izq);
  clearHelp(nodo->der);
  free(nodo);
}

//funcion auxiliar de find()
int findHelp(tNodoArbolBin *nodo, int item){
  if(nodo == NULL) return 0;
  if(getValue(nodo) == item) return 1;
  if(item < getValue(nodo)){
    return findHelp(nodo->izq, item);
  }else{
    return findHelp(nodo->der, item);
  }
}

//funcion auxiliar para insert()
int insertHelp(tNodoArbolBin *nodo, int item){
  if(nodo == NULL){
    nodo = malloc(sizeof(tNodoArbolBin));
    if(nodo == NULL){
      return 0;
    }
    nodo->info = item;
    nodo->izq, nodo->der = NULL;
    return 1;
  }
  if(item < getValue(nodo)){
    insertHelp(nodo->izq, item);
  }else{
    insertHelp(nodo->der, item);
  }
}

//funcion auxiliar inOrden()
void inOrdenHelp(tNodoArbolBin *nodo){
  if(nodo == NULL) return;
  inOrdenHelp(nodo->izq);
  getValue(nodo);
  inOrdenHelp(nodo->der);
}

//funcion auxiliar de preOrden()
void preOrdenHelp(tNodoArbolBin *nodo){
  getValue(nodo);
  preOrdenHelp(nodo->izq);
  preOrdenHelp(nodo->der);
}

//funcion auxiliar de postOrden()
void postOrdenHelp(tNodoArbolBin *nodo){
  postOrdenHelp(nodo->izq);
  postOrdenHelp(nodo->der);
  getValue(nodo);
}






//inicializa un Abb como vacio
void initTree(tABB *T){
  T->raiz = NULL;
  T->nElems = 0;
}

//elimina un elemento en un Abb
void remove(tABB *T, int item){
  return;
}

//insertar un elemento en un Abb
int insert(tABB *T, int item){
  if(find(T, item)){
    insertHelp(T->raiz, item);
    return 1;
  }else{
    return 0;
  }
}

//elimina todos los elementos en un Abb, dejandolo vacio
void clear(tABB *T){
  clearHelp(T->raiz);
  T->raiz = NULL;
  T->nElems = 0;
}

//busca un item en un abb, retorna 0 si no esta 1 si esta
int find(tABB *T, int item){
  return findHelp(T->raiz, item);
}

//obtiene el valor del nodo
int getValue(tNodoArbolBin *nodo){
  return(nodo->info);
}

//cantidad de elementos de un arbol
int size(tABB *T){
  return T->nElems;
}


//recorrido in-orden de un Abb
void inOrden(tABB *T){
  inOrdenHelp(T->raiz);
}

//recorrido pre-orden de un Abb
void preOrden(tABB *T){
  preOrdenHelp(T->raiz);
}

//recorrido en post-orden de un Abb
void postOrden(tABB *T){
  postOrdenHelp(T->raiz);
}
