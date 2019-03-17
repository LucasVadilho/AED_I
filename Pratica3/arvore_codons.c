#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct treeNode treeNode;
struct treeNode {
    int contador;
    char codon[3];
    treeNode *left, *right;
};

treeNode* allocNo(char* data){
    treeNode* no = (treeNode *) malloc(sizeof(treeNode));
    no->contador = 1;
    no->codon[0] = data[0];
    no->codon[1] = data[1];
    no->codon[2] = data[2];
    no->left = NULL;
    no->right = NULL;

    return no;
}

treeNode* insereCodon(treeNode* no, char* codon){
    if(no == NULL){
        no = allocNo(codon);
        return no;
    }

    int dif = strcmp(no->codon, codon);

    if(dif == 0){ //codons iguais
        no->contador++;
        return no;
    }

    if(dif > 0){ //codon novo antes do antigo
        if(no->left == NULL) no->left = allocNo(codon);
        else insereCodon(no->left, codon); 
    } else{ //codon novo depois do antigo 
        if(no->right == NULL) no->right = allocNo(codon);
        else insereCodon(no->right, codon);
    }

    return no;
}

void liberaArvore(treeNode* no){
    if(no != NULL){
        liberaArvore(no->left);
        liberaArvore(no->right);
        printf("%s ", no->codon);
        free(no);
    }
}

void imprimeArvore(treeNode* no){
    if(no != NULL){
        imprimeArvore(no->left);
        int i;
        for(i = 0; i < no->contador; i++){
            printf("%s ", no->codon);
        }
        imprimeArvore(no->right);
    }
}

void main(){
    treeNode* raiz = NULL;    
    char base_atual = getchar();
    char codon[3];
	int i = 0;

	while(base_atual != '0'){
        codon[i] = base_atual;

        if(i == 2) raiz = insereCodon(raiz, codon);
		
		base_atual = getchar();
        i = ((i + 1) % 3);
	}
	
    imprimeArvore(raiz);
    printf("\n");

	liberaArvore(raiz);
    printf("\n");
}