#include <stdio.h>
#include <stdlib.h>

typedef struct no no;
struct no{
    char data;
    no* next;
};

void imprimirLista(no* no){
    while(no != NULL){
        printf("%c", no->data);
        no = no->next;
    }
    printf("\n");
}

no* inserirFim(no* lista, char data){
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
    return lista;
}

no* inserirOrdenado(no* lista, char data){
    no* novo = (no*) malloc(sizeof(no));
    
    if(novo == NULL) return lista;
    
    novo->data = data;
    novo->next = NULL;

    if(lista == NULL) return novo;

    no* anterior = NULL;
    no* atual = lista;
   
    while(atual != NULL){
        if(data < atual->data){
            anterior->next = novo;
            novo->next = atual;
            
            return lista;
        }
        anterior = atual;
        atual = atual->next;
    }
    anterior->next = novo;

    return lista;
}

void main(){
    no* dna;
    no* dnaOrdenado;

    char c;
    while(c = getchar()){
        if(c == '0') break;
        else{
            dna = inserirFim(dna, c);
            dnaOrdenado = inserirOrdenado(dnaOrdenado, c);
        }
    }

    imprimirLista(dna);
    imprimirLista(dnaOrdenado);
}