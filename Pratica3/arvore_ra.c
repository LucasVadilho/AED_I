#include <stdio.h>
#include <stdlib.h>


typedef struct treeNode treeNode;
struct treeNode {
    int data;
    treeNode *left, *right;
};

treeNode* allocNo(int data){
    treeNode* no = (treeNode *) malloc(sizeof(treeNode));
    no->left = NULL;
    no->right = NULL;
    no->data = data;

    return no;
}

treeNode* inserirNo(treeNode* arvore, int data){
    if(arvore == NULL){
        arvore = allocNo(data);
        return arvore;
    }

    if(data >= arvore->data){
        if(arvore->right == NULL) arvore->right = allocNo(data);
        else inserirNo(arvore->right, data);
    } else{
        if(arvore->left == NULL) arvore->left = allocNo(data);
        else inserirNo(arvore->left, data);
    }

    return arvore;
}

void liberaArvore(treeNode* no){
    if(no != NULL){
        liberaArvore(no->left);
        liberaArvore(no->right);
        printf("%d ", no->data);
        free(no);
    }
}

void imprimeArvore(treeNode* no){
    if(no != NULL){
        imprimeArvore(no->left);
        printf("%d\n", no->data);
        imprimeArvore(no->right);
    }
}

void imprimeProfundidade(treeNode* no, int valor, int profundidade){
    if(no == NULL){
        printf("P=-1\n");
        return;
    }
    
    if(no->data == valor){
        printf("P=%d\n", profundidade);
        return;
    }
    
    if(valor > no->data) imprimeProfundidade(no->right, valor, ++profundidade);
    else imprimeProfundidade(no->left, valor, ++profundidade);
}

void main(){
    treeNode* raiz = NULL;

    char operacao;
    int valor;
    scanf("%c %d", &operacao, &valor);
    while (operacao != 'E'){
        if (operacao == 'I'){
            raiz = inserirNo(raiz, valor);
        }
        if (operacao == 'P'){
            imprimeProfundidade(raiz, valor, 0);
        }
        scanf("%c %d", &operacao, &valor);
    }

    liberaArvore(raiz);
}
