#include <stdio.h>
#include <stdlib.h>

struct Node {
  int data;
  struct Node *left;
  struct Node *right;
};
typedef struct Node Node;


Node* criarArvoreCompleta(Node *raiz, int *V, int n);
Node* inserirElemento(int valor, Node *raiz);
void liberarArvore(Node* raiz);
void imprimirArvore(Node *raiz);
int altura(Node *raiz);


int main(void) {
  int n, i;
  Node *raiz=NULL;

  scanf("%d", &n);
  int *V = (int *) malloc(n*sizeof(int));
  for (i=0; i<n; i++)
      *(V+i) = i;
  
  raiz = criarArvoreCompleta(raiz, V, n);

  imprimirArvore(raiz);
  printf("Altura da arvore = %d\n", altura(raiz));

  liberarArvore(raiz);
  return 0;
}


/* Funcoes */
Node* inserirElemento(int valor, Node *raiz) {
  if (raiz==NULL) {
    Node *novo  = (Node *) malloc(sizeof(Node));
    novo->data  = valor;
    novo->left  = NULL;
    novo->right = NULL;
    return novo;
  }

  if (raiz->data < valor)
    raiz->right = inserirElemento(valor, raiz->right);
  if (raiz->data > valor)
    raiz->left  = inserirElemento(valor, raiz->left);
  return raiz;
}


void liberarArvore(Node* raiz) {
  if (raiz!=NULL) {
    liberarArvore(raiz->left);
    liberarArvore(raiz->right);
    free(raiz);
  }
}


int altura(Node *raiz) {
  if (raiz==NULL)
    return -1;
  else {
    int he = altura(raiz->left);
    int hd = altura(raiz->right);
    if (he<hd)
      return hd+1;
    else
      return he+1;
  }
}


void imprimirArvore(Node *raiz) {
  if (raiz!=NULL) {
    imprimirArvore(raiz->left);
    printf("%d\n", raiz->data);
    imprimirArvore(raiz->right);
  }
}



Node* criarArvoreCompleta(Node *raiz, int *V, int n) {
  if (n>0) {
    int q=n/2;
    raiz = inserirElemento(*(V+q), raiz);
    raiz = criarArvoreCompleta(raiz, V, q);
    raiz = criarArvoreCompleta(raiz, V+q+1, n-q-1);
  }
  return raiz;
}

