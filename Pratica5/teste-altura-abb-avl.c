#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
    int height;
};
typedef struct Node Node;


Node* inserirElemento(int valor, Node *raiz);
Node* rotacaoADireita(Node* y);
Node* rotacaoAEsquerda(Node* x);
Node* buscaElemento(Node *raiz, int chave);
void imprimirArvore(Node *raiz);
void liberarArvore(Node* raiz);
int fatorDeBalanceamento(Node* raiz);
int altura(Node* raiz);
int max(int a, int b);



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
int altura(Node* raiz) {
    if (raiz==NULL)
        return -1;
    else
        return raiz->height;
}

int max(int a, int b) {
    if (a>b)
        return a;
    else
        return b;
}


Node* rotacaoADireita(Node* y) {
    Node* x  = y->left;
    Node* T2 = x->right;
    
    // rotacao
    x->right = y;
    y->left  = T2;
    
    // atualizacao de altura
    y->height = 1 + max( altura(y->left) , altura(y->right) );
    x->height = 1 + max( altura(x->left) , altura(x->right) );
    
    return x;
}

Node* rotacaoAEsquerda(Node* x) {
    Node* y  = x->right;
    Node* T2 = y->left;
    
    // rotacao
    y->left  = x;
    x->right = T2;
    
    // atualizacao de altura
    x->height = 1 + max( altura(x->left) , altura(x->right) );
    y->height = 1 + max( altura(y->left) , altura(y->right) );
    
    return y;
}

int fatorDeBalanceamento(Node* raiz) {
    if (raiz==NULL)
        return 0;
    else
        return altura(raiz->left) - altura(raiz->right);
}


Node* inserirElemento(int valor, Node *raiz) {
    
    // insercao na ABB -- versao recursiva
    if (raiz==NULL) {
        Node *novo   = (Node *) malloc(sizeof(Node));
        novo->data   = valor;
        novo->left   = NULL;
        novo->right  = NULL;
        novo->height = 0;
        return novo;
    }
    
    if (valor == raiz->data)
        return raiz;
    else {
        if (valor < raiz->data) 
            raiz->left  = inserirElemento(valor, raiz->left);
        else 
            raiz->right = inserirElemento(valor, raiz->right);
    }
    
    // atualizacao da altura do Node antecessor
    raiz->height = 1 + max( altura(raiz->left), altura(raiz->right) );
    
    // fator de balanceamento
    int fb = fatorDeBalanceamento(raiz);

    // ----------------------------------------------------------
    // se o Node estiver desbalanceado, entao temos 4 alternativas
    
    // Caso LL:
    if ( fb>1  && valor < raiz->left->data) {
        printf("\n* Rotacao LL");
        return rotacaoADireita(raiz);
    }
        
    // Caso RR:
    if ( fb<-1 && valor > raiz->right->data) {
        printf("\n* Rotacao RR");
        return rotacaoAEsquerda(raiz);
    }
    
    // Caso LR:
    if ( fb>1  && valor > raiz->left->data) {
        printf("\n* Rotacao LR");
        raiz->left = rotacaoAEsquerda(raiz->left);
        return rotacaoADireita(raiz);
    }
    
    // Caso RL:
    if ( fb<-1 && valor < raiz->right->data) {
        printf("\n* Rotacao RL");
        raiz->right = rotacaoADireita(raiz->right);
        return rotacaoAEsquerda(raiz);
    }
    
    return raiz;
}


void imprimirArvore(Node *raiz) {
  if (raiz!=NULL) {
    imprimirArvore(raiz->left);
    printf("\n%d [fb=%d]", raiz->data, fatorDeBalanceamento(raiz));
    imprimirArvore(raiz->right);
  }
}


void liberarArvore(Node* raiz) {
  if (raiz!=NULL) {
    liberarArvore(raiz->left);
    liberarArvore(raiz->right);
    free(raiz);
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

