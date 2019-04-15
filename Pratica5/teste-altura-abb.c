#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node {
  int data;
  struct Node *left;
  struct Node *right;
};
typedef struct Node Node;


Node *inserirElemento(int valor, Node *raiz);
void liberarArvore(Node* raiz);
int altura(Node *raiz);
void imprimirArvore(Node *raiz);
Node* buscaElemento(Node *raiz, int chave);


int main(void) {
  int n, valor;
  Node *raiz=NULL;

  // Usando o tempo atual como semente para geracao de numeros aleatorios
  srand(time(0)); 

  scanf("%d", &n);
  
  while (n>0) {
    valor = rand();
    if (buscaElemento(raiz, valor)==NULL) {
      raiz = inserirElemento(valor, raiz);
      n--;
    }
    else 
      printf("Elemento ja existente na arvore: %d\n", valor);
  }

  imprimirArvore(raiz);
  printf("Altura da arvore = %d\n", altura(raiz));

  liberarArvore(raiz);
  return 0;
}


/* Funcoes */
Node *inserirElemento(int valor, Node *raiz) {
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


Node* buscaElemento(Node *raiz, int chave) {
  if (raiz==NULL)
    return raiz;
  if (raiz->data==chave)
    return raiz;
  
  if (raiz->data < chave)
    return buscaElemento(raiz->right, chave);
  else 
    return buscaElemento(raiz->left, chave);
}

