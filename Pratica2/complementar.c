#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    char data;
    struct no* next;
} no;

typedef struct pilha{
    no* topo;
} pilha;

no* allocNo(){
    no* novo;
    if((novo = (no *) malloc(sizeof(no))) == NULL){
        printf("Acabou a memória.");
        exit(1);
    }
    return novo;
}

pilha* allocPilha(){
    pilha* p;
    if((p = (pilha *) malloc(sizeof(pilha))) == NULL){
        printf("Acabou a memória.");
        exit(1);
    }
    p->topo = NULL;
    return p;
}

pilha* empilha(pilha* p, char c){
    no* novo = allocNo();
    novo->data = c;
    novo->next = p->topo;

    p->topo = novo;
    return p;
}

char desempilha(pilha* p){
    no* temp = p->topo;
    if(temp != NULL){
        p->topo = (p->topo)->next;
        char c = temp->data;
        free(temp);

        return c;
    }
    return '0';
}

void liberaPilha(pilha* p){
    no* atual = p->topo;

    while(atual != NULL){
        no* temp = atual;
        atual = atual->next;
        free(temp);
    }
    free(p);
}

void imprimePilha(pilha* p){
    no* atual = p->topo;

    while(atual != NULL){
        printf("%c", atual->data);
        atual = atual->next;
    }
    printf("\n");
}

pilha* invertePilha(pilha* p){
    pilha* invertida = allocPilha();
    char c = desempilha(p);
    while(c != '0'){
        invertida = empilha(invertida, c);
        c = desempilha(p);
    }
    
    return invertida;
}

char baseComplementar(char base){
    switch(base){
        case 'A':
            return 'T';
            break;
        case 'T':
            return 'A';
            break;
        case 'C':
            return 'G';
            break;
        case 'G':
            return 'C';
            break;
        default:
            return '0';
            break;
    }
}

int verificaComplementar(pilha* fita1, pilha* fita2){
    while(fita1->topo != NULL){
        if(fita2->topo == NULL) return 0;
        if(desempilha(fita1) != baseComplementar(desempilha(fita2))) return 0;
    }
   
    if(fita2->topo != NULL) return 0;
   
    return 1;
}

void main(){
    pilha* fita1 = allocPilha();
    pilha* fita2 = allocPilha();
    
    char c = getchar();
    while(c != '0'){
        fita1 = empilha(fita1, c);
        c = getchar();
    }

    getchar(); //\n
    
    c = getchar();
    while(c != '0'){
        fita2 = empilha(fita2, c);
        c = getchar();
    }

    pilha* fita1Invertida = invertePilha(fita1);

    printf("%d\n", verificaComplementar(fita1Invertida, fita2));

    liberaPilha(fita1);
    liberaPilha(fita1Invertida);
    liberaPilha(fita2);
}