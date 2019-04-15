#include <stdio.h>
#include <stdlib.h>

#define COUNT 10

typedef struct avlTreeNode avlTreeNode;
struct avlTreeNode {
	int data;
	int height;
	avlTreeNode *left, *right;
};

//#G4G
void print2DUtil(avlTreeNode *root, int space) 
{ 
    // Base case 
    if (root == NULL) 
        return; 
  
    // Increase distance between levels 
    space += COUNT; 
  
    // Process right child first 
    print2DUtil(root->right, space); 
  
    // Print current node after space 
    // count 
    printf("\n"); 
    for (int i = COUNT; i < space; i++) 
        printf(" "); 
    printf("%d\n", root->data); 
  
    // Process left child 
    print2DUtil(root->left, space); 
} 


int altura(avlTreeNode *n) {
    if (n == NULL) return -1;
	int esq = (n->left != NULL ? n->left->height : -1);
	int dir = (n->right != NULL ? n->right->height : -1);
	return (esq > dir ? esq + 1 : dir + 1);
}

int fatorBalanceamento(avlTreeNode *raiz) {
	int esq = altura(raiz->left);
	int dir = altura(raiz->right);
	return (esq - dir);
}

avlTreeNode *rotaciona_esquerda(avlTreeNode *raiz) {
	avlTreeNode *arvDireita = raiz->right;

	raiz->right = arvDireita->left;
	arvDireita->left = raiz;

	raiz->height = altura(raiz);
	arvDireita->height = altura(arvDireita);
	return arvDireita;
}

avlTreeNode *rotaciona_direita(avlTreeNode *raiz) {
	avlTreeNode *arvEsquerda = raiz->left;

	raiz->left = arvEsquerda->right;
	arvEsquerda->right = raiz;

	raiz->height = altura(raiz);
	arvEsquerda->height = altura(arvEsquerda);
	return arvEsquerda;
}

avlTreeNode *balancear(avlTreeNode *raiz) {
	int fb = fatorBalanceamento(raiz);
	if (fb > 1) {
		int fb_esq = fatorBalanceamento(raiz->left);
		if (fb_esq >= 0) {
			//printf("Rotacao simples direita\n");
		} else {
			raiz->left = rotaciona_esquerda(raiz->left);
			//printf("Rotacao dupla direita\n");
		}
		raiz = rotaciona_direita(raiz);
	} else if (fb < -1) {
		int fb_dir = fatorBalanceamento(raiz->right);
		if (fb_dir <= 0) {
			//printf("Rotacao simples esquerda\n");
		} else {
			raiz->right = rotaciona_direita(raiz->right);
			//printf("Rotacao dupla esquerda\n");
		}
		raiz = rotaciona_esquerda(raiz);
	}
	return raiz;
}

avlTreeNode *inserir(avlTreeNode *raiz, int valor) {
	if (raiz == NULL) {
		raiz = malloc(sizeof(avlTreeNode));
		raiz->data = valor;
		raiz->left = NULL;
		raiz->right = NULL;
		raiz->height = 0;
		return raiz;
	}
	if (valor < raiz->data)
		raiz->left = inserir(raiz->left, valor);
	else if (valor > raiz->data)
		raiz->right = inserir(raiz->right, valor);

	raiz->height = altura(raiz);

	raiz = balancear(raiz);
	
	return raiz;
}

void liberaArvore(avlTreeNode *raiz) {
	if (raiz == NULL) return;
	liberaArvore(raiz->left);
	liberaArvore(raiz->right);
	printf("%d ", raiz->data);
	free(raiz);
}

avlTreeNode* min(avlTreeNode* raiz){
    if(raiz->left == NULL) return raiz;
    else return(min(raiz->left));
}

avlTreeNode* remover(avlTreeNode* root, int key) {
    if(root == NULL) return NULL;

    if(key > root->data) root->right = remover(root->right, key);
    else if(key < root->data) root->left = remover(root->left, key);
    else{
        if(root->right == NULL){
            avlTreeNode* tmp = root->left;
            free(root);

            return tmp;
        }

        if(root->left == NULL){
            avlTreeNode* tmp = root->right;
            free(root);
            return tmp;
        }

        avlTreeNode* tmp = min(root->right);
        root->data = tmp->data;
        root->right = remover(root->right, tmp->data);
    }

    if(root == NULL) return NULL;

    root->height = altura(root);

    root = balancear(root);

    return root;
    //Com ajuda do geeksforgeeks
}

void imprimir(avlTreeNode* raiz){
    if(raiz != NULL){
        imprimir(raiz->left);
        printf("%d ", raiz->data);
        imprimir(raiz->right);
    }
}

void main() {
    avlTreeNode* arv = NULL;

    int n;
    scanf("%d", &n);

    int i, key;
    for(i = 0; i < n; i++){
        scanf("%d", &key);
        arv = inserir(arv, key);
    }

    printf("A=%d\n", altura(arv));

    scanf("%d", &key);
    arv = remover(arv, key);

    printf("A=%d\n", altura(arv));
    
    printf("[");
    liberaArvore(arv);
    printf("]\n");
}
