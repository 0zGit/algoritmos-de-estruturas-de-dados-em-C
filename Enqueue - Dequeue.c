#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

/////////////////////////////////////////////////////////////////////////////////////
// PROGRAMA 4

typedef struct SNoh{
    int valor;
    struct SNoh *prox; // Vai apontar para o pr�ximo elemento
}SNoh;

typedef SNoh *NohPtr;

void Consulta(NohPtr inicio);
NohPtr Enqueue(NohPtr inicio,int valor);
NohPtr Dequeue(NohPtr inicio);

int main(){
	setlocale(LC_ALL,"");
	
	int valor,escolhaMenu;
	
	NohPtr inicio = NULL;
	
	MENU:
	printf("\n\n+++++++++++++++++++++++");
	printf("\n+\tEscolha uma opera��o ==>");
	printf("\n+\t\t0 - Encerra o programa");
	printf("\n+\t\t1 - Consulta");
	printf("\n+\t\t2 - Enqueue");
	printf("\n+\t\t3 - Dequeue");
	printf("\n>> ");
	scanf("%d",&escolhaMenu);
	
	switch(escolhaMenu){
		case 0:{
			printf("\n\nFechando programa...");
			return 0;
		} 
		case 1:{
			Consulta(inicio);
			break;
		}
		case 2:{
			printf("\nDigite um inteiro a ser inserido na lista: ");
			scanf("%d",&valor);
			inicio =  Enqueue(inicio,valor);
			break;
		}
		case 3:{
			inicio = Dequeue(inicio);
			break;
		}
		default:{
			printf("\nInv�lido. Retornando ao Menu...");
			break;
		}
	}
	goto MENU;
}

void Consulta(NohPtr inicio){
	if(inicio == NULL) printf("\nNenhum elemento a ser exibido.\nRetornando ao menu...");
	else{
		if((*inicio).prox == NULL) printf("\nPr�ximo elemento de Dequeue: %d",(*inicio).valor);
		else{
			NohPtr p;
			p = inicio;
			while((*p).prox != NULL) p = (*p).prox;
			printf("\nPr�ximo elemento de Dequeue: %d",(*p).valor);
		}
	}
}


NohPtr Enqueue(NohPtr inicio,int valor){
    NohPtr p,novoNoh;
    
    p = inicio;
    
    novoNoh = (NohPtr)malloc(sizeof(SNoh));
	(*novoNoh).valor = valor;
	(*novoNoh).prox = p;
	inicio = novoNoh;
	
	printf("\nElemento inserido.\nRetornando ao menu...");
    return inicio;
}


NohPtr Dequeue(NohPtr inicio){
    if(inicio == NULL){
    	printf("\nNenhum elemento a ser removido.\nRetornando ao menu...");
    	return NULL;
	}
    else{
    	if((*inicio).prox == NULL){
    		free(inicio);
    		inicio = NULL;
    		printf("\nRemovido �nico elemento da lista.\nRetornando ao menu...");
		}
		else{
			NohPtr nohAtual,nohAnterior;
    		nohAtual = inicio;
			while((*nohAtual).prox != NULL){
				nohAnterior = nohAtual; //salvando o n� anterior
				nohAtual = (*nohAtual).prox; // passando o pr�ximo
			} // quando sair, o nohAtual ser� o �ltimo (antes do NULL)
			free(nohAtual); // liberamos o �ltimo
			(*nohAnterior).prox = NULL; // e o anterior, agora �ltimo, ser� apontado para NULL
			printf("\nRemovido �ltimo elemento da lista.\nRetornando ao menu...");
		}
	}
	return inicio;
}
