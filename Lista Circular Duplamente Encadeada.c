#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

/////////////////////////////////////////////////////////////////////////////////////
// PROGRAMA 6 (verifica��o de elemento n�o existente na remo��o n�o funcionando)

typedef struct SNoh{
    int valor;
    struct SNoh *prox;
    struct SNoh *ant;
}SNoh;

typedef SNoh *NohPtr;

void ExibeLista(NohPtr inicio);
NohPtr Insercao(NohPtr inicio,int valor);
NohPtr Remocao(NohPtr inicio,int valor);

int main(){
	setlocale(LC_ALL,"");
	
	int valor,escolhaMenu;
	
	NohPtr inicio = NULL;
	
	MENU:
	printf("\n+++++++++++++++++++++++");
	printf("\n+\tEscolha uma opera��o ==>");
	printf("\n+\t\t0 - Encerra o programa");
	printf("\n+\t\t1 - Exibir lista");
	printf("\n+\t\t2 - Inser��o");
	printf("\n+\t\t3 - Remo��o");
	printf("\n>> ");
	scanf("%d",&escolhaMenu);
	
	switch(escolhaMenu){
		case 0:{
			printf("\n\nFechando programa...");
			return 0;
		} 
		case 1:{
			if(inicio == NULL) printf("\nNenhum elemento a ser exibido.\nRetornando ao menu...");
			else ExibeLista(inicio);
			break;
		}
		case 2:{
			NohPtr p=inicio;
			printf("\nDigite um inteiro a ser inserido na lista: ");
			scanf("%d",&valor);
			if(p == NULL){
				inicio =  Insercao(inicio,valor);
				break;
			}
			else if((*p).valor == valor){
				printf("\nElemento � o primeiro da lista.\nRetornando ao menu...");
				break;
			}
			else{
				p = inicio;
				while((*p).prox != NULL){
					if(valor == (*p).valor){
						printf("\nElemento j� inserido, favor inserir outro.\nRetornando ao menu...");
						break;
					}
					else p = (*p).prox;
				}
				printf("\nIniciando inser��o.");
				inicio =  Insercao(inicio,valor);
			}
			break;
		}
		case 3:{
			if(inicio == NULL) printf("\nNenhum elemento a ser removido.\nRetornando ao menu...");
			else{
				printf("\nDigite o elemento a ser removido da lista: ");
				scanf("%d",&valor);
				NohPtr p=inicio;
				while(1){
					if((*p).valor == valor){
						printf("\nIniciando remo��o.");
						inicio = Remocao(inicio,valor);
						break;
					}
					else if(p == NULL){ // n�o funcionando...
						printf("\nElemento n�o encontrado.\nRetornando ao menu...");
						break;
					}
					p = (*p).prox;
				}
			}
			break;
		}
		default:{
			printf("\nInv�lido. Retornando ao Menu...");
			break;
		}
	}
	goto MENU;
}

void ExibeLista(NohPtr inicio){
	NohPtr p;
    p = inicio;
    printf("\nImprimindo lista Duplamente Encadeada:\n");
    while(p != NULL){
    	printf("%d\t",(*p).valor);
    	p = (*p).prox;
	}
}
NohPtr Insercao(NohPtr inicio, int valor){
	NohPtr novoNoh;
	if(inicio == NULL){
		novoNoh = (NohPtr)malloc(sizeof(SNoh));
		(*novoNoh).valor = valor;
		(*novoNoh).prox = NULL;
		(*novoNoh).ant = NULL;
		inicio = novoNoh;
		printf("\nPrimeiro elemento inserido.\nRetornando ao menu...");
	}
	else{
		NohPtr p;
		p = inicio;
		if(valor < (*p).valor){ // � o menor
			novoNoh = (NohPtr)malloc(sizeof(SNoh));
			(*novoNoh).valor = valor;
			(*novoNoh).prox = p;
			(*novoNoh).ant = NULL;
			inicio = novoNoh;
			(*p).ant = inicio;
			printf("\nElemento inserido ao in�cio da lista.\nRetornando ao menu...");
		}
		else{
			NohPtr p = inicio;
			while((*p).prox != NULL) p = (*p).prox; // sair� com p sendo o �ltimo elemento (antes de NULL)
			if(valor > (*p).valor){ // � o maior ?
				novoNoh = (NohPtr)malloc(sizeof(SNoh));
				(*novoNoh).valor = valor;
				(*p).prox = novoNoh;
				(*novoNoh).ant = p;
				(*novoNoh).prox = NULL;
				printf("\nElemento inserido ao final da lista.\nRetornando ao menu...");
			}
			else{ // no meio
				NohPtr nohAtual = inicio,nohAnterior = inicio;
				while(valor > (*nohAtual).valor){
					if((*nohAtual).prox != inicio){
						nohAnterior = nohAtual; //salvando o n� anterior
						nohAtual = (*nohAtual).prox; // passando o pr�ximo
					}
				} // quando sair, nohAtual ser� maior que valor e nohAnterior ser� menor
				novoNoh = (NohPtr)malloc(sizeof(SNoh));
				(*novoNoh).valor = valor;
				(*novoNoh).prox = nohAtual;
				(*novoNoh).ant = nohAnterior;
				(*nohAnterior).prox = novoNoh;
				(*nohAtual).ant = novoNoh;
				printf("\nElemento inserido ao meio da lista.\nRetornando ao menu...");
			}
		}
	}
	return inicio;
}
NohPtr Remocao(NohPtr inicio,int valor){
	NohPtr p = inicio;
	if(valor == (*p).valor){ // primeiro
		p = (*inicio).prox; // pr�ximo
		if(p == NULL){ // se for lista de um �nico elemento
			free(inicio); // liberou o antigo valor de inicio
			inicio = p; // inicio ser� NULL
		}
		else (*p).ant = NULL; // da�, se n�o for uma lista de um �nico elemento (*p).prox != NULL, simplesmente o anterior de p prox � NULL
		return inicio;
	}
	else{
		NohPtr nohAnterior = inicio;
		p = (*p).prox;
		while(p != NULL){ // vamos percorrer todos para comparar um por um
			if((valor==(*p).valor) && ((*p).prox==NULL)){ // elemento foi encontrado na lista e � o �ltimo
				(*nohAnterior).prox = NULL; // o anterior do �ltimo apontar� para NULL
				free(p);// da� o �ltimo ser� liberado
			}
			else if(((*p).valor==valor) && ((*p).prox!=NULL)){// elemento foi encontrado na lista e n�o � o �ltimo
				(*nohAnterior).prox = p;
				(*p).ant = nohAnterior;
				free(p);
			}
			p = (*p).prox;
			nohAnterior = (*nohAnterior).prox;
		}
	}
}
