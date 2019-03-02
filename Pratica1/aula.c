#include <stdio.h>
#include <stdlib.h>

typedef struct no no;
struct no{
    int data;
    no* next;
};

void imprimirLista(no* no){
    while(no != NULL){
        printf("%d ", no->data);
        no = no->next;
    }
    printf("\n");
}

void imprimirListaRecursivo(no* no){
    if(no != NULL){
        printf("%d ", no->data);
        imprimirListaRecursivo(no->next);
    } else printf("\n");
}

no* inserirFim(no* lista, int data){
    no* novo = (no*) malloc(sizeof(no));
    
    if(novo == NULL) return lista;
    
    novo->data = data;
    novo->next = NULL;

    if(lista == NULL) return novo;

    no* atual = lista;
    while(atual->next != NULL){
        atual = atual->next;
    }
    
    atual->next = novo;
}

void main(){
    no* inicio = inserirFim(inicio, 5);

    inserirFim(inicio, 7);
    imprimirLista(inicio);
    inserirFim(inicio, 9);
    imprimirListaRecursivo(inicio);
    inserirFim(inicio, 10);
    imprimirLista(inicio);
    imprimirListaRecursivo(inicio);
}