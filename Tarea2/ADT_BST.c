//bynary search tree
#include <stdio.h>
#include <stdlib.h>

typedef struct nodoArbolBin{
    int info;
    struct nodoArbolBin *left;
    struct nodoArbolBin *right;
} Node;

/*****
*
Node* newNode()
******
*
Genera un nuevo nodo.
******
*
Input:
*
int item : Valor del nodo.
*
.......
******
*
Returns:
*
Node* , Retorna un Nodo.
*****/
Node *newNode(int item) {
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->info = item;
    temp->left = temp->right = NULL;
    return temp;
}

/*****
*
Node* insertHelp()
******
*
Ayuda a la funcion insert()
******
*
Input:
*
Node* node : Raíz del árbol.
int item : Nodo que se quiere añadir al árbol.
*
.......
******
*
Returns:
*
Node* Retorna la raíz del árbol.
*****/
Node *insertHelp(Node *node, int item) {
    if (node == NULL) return newNode(item);
    if (item < node->info)
        node->left = insertHelp(node->left, item);
    else
        node->right = insertHelp(node->right, item);
    return node;
}


/*****
*
Node* initTree()
******
*
Inicializa un Árbol
******
*
Input:
*

*
.......
******
*
Returns:
*
Node* , Retorna un arbol vacio.
*****/
Node* initTree(){
    return NULL;
}

/*****
*
int getValue()
******
*
Obtiene el valor de un nodo
******
*
Input:
*
Node* nodo : Nodo del que se quiere obtener el valor.
*
.......
******
*
Returns:
*
int , Retorna el valor del nodo.
*****/
int getValue(Node *nodo){
    return(nodo->info);
}

/*****
*
Node* getRight()
******
*
Obtiene el hijo derecho de un nodo.
******
*
Input:
*
Node* nodo : Nodo del que se quiere obtener el hijo derecho.
*
.......
******
*
Returns:
*
Node* , Retorna el hijo derecho.
*****/
Node* getRight(Node* nodo){
    return nodo->right;
}

/*****
*
Node* getLeft()
******
*
Obtiene el hijo izquierdo de un nodo.
******
*
Input:
*
Node* nodo : Nodo del que se quiere obtener el hijo izquierdo.
*
.......
******
*
Returns:
*
Node* , Retorna el hijo izquierdo.
*****/
Node* getLeft(Node* nodo){
    return nodo->left;
}


/*****
*
int find()
******
*
Ve si un nodo esta presente en el Árbol.
******
*
Input:
*
Node* nodo : Raíz del Árbol.
int item: Valor que se busa en el arbol
*
.......
******
*
Returns:
*
Node* Retorna 1 si lo encontro, o 0 si No.
*****/
int find(Node *nodo, int item){
    if(nodo == NULL) return 0;
    if(getValue(nodo) == item) return 1;
    if(item < getValue(nodo)){
        return find(nodo->left, item);
    }else{
        return find(nodo->right, item);
    }
}

/*****
*
Node* insert()
******
*
Inserta un nodo en el árbol.
******
*
Input:
*
Node* node : Raíz del árbol.
int item : Nodo que se quiere insertar.
*
.......
******
*
Returns:
*
Node* , Retorna la raíz del árbol.
*****/
Node* insert(Node *node, int item){
    if(!find(node, item))
        return insertHelp(node, item);
    return node;
}


/*****
*
Node* findMax()
******
*
Obtiene el mayor valor de un árbol.
******
*
Input:
*
Node* T : Raíz del árbol.
*
.......
******
*
Returns:
*
Node* , Retorna el maximo valor de un árbol.
*****/
Node* findMax(Node *T){
    if(T == NULL) return NULL;
    else if(T->right != NULL) // node with minimum value will have no left child
        return findMax(T->right); // left most element will be minimum
    return T;
}

/*****
*
Node* remove_()
******
*
Borra un Nodo del árbol.
******
*
Input:
*
Node* T : Raíz del árbol.
int item : Elemento que se quiere borrar.
*
.......
******
*
Returns:
*
Node* , Retorna la raíz del arbol.
*****/
Node* remove_(Node *T, int item){
    // Se busca el item a ser removido
    if(T==NULL)
        return NULL;
    if (item>T->info)
        T->right = remove_(T->right, item);
    else if(item<T->info)
        T->left = remove_(T->left, item);
    else{
        //Sin hijos
        if(T->left==NULL && T->right==NULL){
            free(T);
            return NULL;
        }
        //Un solo hijo
        else if(T->left==NULL || T->right==NULL){
            Node *temp;
            if(T->left==NULL)
                temp = T->right;
            else
                temp = T->left;
            free(T);
            return temp;
        }
        //Dos hijos
        else{
            //Find Max
            Node *temp = findMax(T->left);
            T->info = temp->info;
            T->left = remove_(T->left, temp->info);
        
        }
    }
    return T;
}


/*****
*
void preOrden()
******
*
Recorre el arbol en preorden y hace print de los nodos.
******
*
Input:
*
Node* T : Raíz del árbol
*
.......
******
*
Returns:
*
void, No Retorna nada.
*****/
void preOrden(Node *T){
    if(T != NULL){
        printf("%d ", getValue(T));
        preOrden(T->left);
        preOrden(T->right);
    }
}