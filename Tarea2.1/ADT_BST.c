//bynary search tree
#include <stdio.h>
#include <stdlib.h>

typedef struct nodoArbolBin{
    int info;
    struct nodoArbolBin *left;
    struct nodoArbolBin *right;
} Node;

/* Auxiliar functions */
Node *newNode(int item) {
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->info = item;
    temp->left = temp->right = NULL;
    return temp;
}

Node *insertHelp(Node *node, int item) {
    if (node == NULL) return newNode(item);
    if (item < node->info)
        node->left = insertHelp(node->left, item);
    else
        node->right = insertHelp(node->right, item);
    return node;
}



//inicializa un Abb como vacio
Node* initTree(){
    return NULL;
}

//obtiene el valor del nodo
int getValue(Node *nodo){
    return(nodo->info);
}

Node* getRight(Node* nodo){
    return nodo->right;
}

Node* getLeft(Node* nodo){
    return nodo->left;
}

//funcion auxiliar de find()
int find(Node *nodo, int item){
    if(nodo == NULL) return 0;
    if(getValue(nodo) == item) return 1;
    if(item < getValue(nodo)){
        return find(nodo->left, item);
    }else{
        return find(nodo->right, item);
    }
}

Node* insert(Node *node, int item){
    if(!find(node, item))
        return insertHelp(node, item);
    return node;
}

//function to find the minimum value in a node
Node* findMin(Node *T){
    if(T == NULL) return NULL;
    else if(T->left != NULL) // node with minimum value will have no left child
        return findMin(T->left); // left most element will be minimum
    return T;
}

Node* findMax(Node *T){
    if(T == NULL) return NULL;
    else if(T->right != NULL) // node with minimum value will have no left child
        return findMax(T->right); // left most element will be minimum
    return T;
}

Node* remove_(Node *T, int item){
    //searching for the item to be removed
    if(T==NULL)
        return NULL;
    if (item>T->info)
        T->right = remove_(T->right, item);
    else if(item<T->info)
        T->left = remove_(T->left, item);
    else{
        //No Children
        if(T->left==NULL && T->right==NULL){
            free(T);
            return NULL;
        }
        //One Child
        else if(T->left==NULL || T->right==NULL){
            Node *temp;
            if(T->left==NULL)
                temp = T->right;
            else
                temp = T->left;
            free(T);
            return temp;
        }
        //Two Children
        else{
            // Find Min
            /*
            Node *temp = findMin(T->right);
            T->info = temp->info;
            T->right = remove_(T->right, temp->info);
            */
            //Find Max
            Node *temp = findMax(T->left);
            T->info = temp->info;
            T->left = remove_(T->left, temp->info);
        
        }
    }
    return T;
}

//elimina todos los elementos en un Abb, dejandolo vacio
void clear(Node *T){
    if(T == NULL) return;
    clear(T->left);
    clear(T->right);
    free(T);
}

// Recorrido preOrden
void preOrden(Node *T){
    if(T != NULL){
        //printf("%d ", getValue(T));
        preOrden(T->left);
        preOrden(T->right);
    }
}