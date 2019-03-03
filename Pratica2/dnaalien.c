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
        if(atual->data > data){
            if(anterior != NULL) anterior->next = novo;
            novo->next = atual;

            if(atual == lista) return novo;
            else return lista;
        }

        anterior = atual;
        atual = atual->next;
    }

    anterior->next = novo;
    return lista;
}

no* removerBases(no* dna){
    no* atual = dna;
    no* anterior = NULL;
    int removeuInicio = 0;

    while(atual != NULL){
        if(atual->data == 'C' || atual->data == 'G'){
            no* tmp = atual;
            if(anterior == NULL){
                dna = dna->next;
                removeuInicio = 1;
            }
            else{
                anterior->next = atual->next;
                atual = anterior;
            }
            free(tmp);
        }
        
        if(removeuInicio == 1){
           atual = dna;
           removeuInicio = 0;
        } else{
            anterior = atual;
            atual = atual->next;
        }
    }

    return dna;
}

void liberarLista(no* lista){
    no* atual = lista;
    while(atual != NULL){
        no* temp = atual;
        atual = atual->next;
        free(temp);
    }
}

void main(){
    no* dna;

    char c;
    while(c = getchar()){
        if(c == '0') break;
        else dna = inserirFim(dna, c);
    }

    imprimirLista(dna);
    dna = removerBases(dna);
    imprimirLista(dna);

    liberarLista(dna);
}