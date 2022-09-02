#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

/////////////////////////////////////////////////////////////////////////////////////
// PROGRAMA 2

typedef struct SNoh{
    int valor;
    struct SNoh *prox; // Vai apontar para o pr�ximo elemento
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
	printf("\n\n+++++++++++++++++++++++");
	printf("\n+\tEscolha uma opera��o ==>");
	printf("\n+\t\t0 - Encerra o programa");
	printf("\n+\t\t1 - Exibir todos os elementos da pilha");
	printf("\n+\t\t2 - Insercao");
	printf("\n+\t\t3 - Remocao");
	printf("\n>> ");
	scanf("%d",&escolhaMenu);
	
	switch(escolhaMenu){
		case 0:{
			printf("\n\nFechando programa...");
			return 0;
		} 
		case 1:{
			ExibeLista(inicio);
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
				printf("\nElemento j� inserido na lista.\nRetornando ao menu...");
				break;
			}
			else{
				p = inicio;
				while((*p).prox != inicio){
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
				NohPtr p;
				p = inicio;
				while(p != NULL){
					if((*p).valor == valor){
						printf("\nElemento encontrado.\nIniciando Remo��o...");
						inicio = Remocao(inicio,valor);
						break;
					}
					p = (*p).prox;
				}
				if(p == NULL) printf("\nElemento n�o encontrado.\nRetornando ao menu...");
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
	if(inicio == NULL) printf("\nNenhum elemento a ser exibido.\nRetornando ao menu...");
	else{
		NohPtr p;
	    p = inicio;
	    printf("\nLista:\n");
	    if((*p).prox == NULL) printf("%d\t",(*p).valor);
	    else{
	    	while((*p).prox != NULL){
	    		printf("%d\t",(*p).valor);
	    		p = (*p).prox;
			}
			if((*p).prox == NULL) printf("%d\t",(*p).valor);
		}
		printf("\nLista impressa.\nRetornando ao Menu...");
	}
}

NohPtr Insercao(NohPtr inicio,int valor){
	NohPtr novoNoh;
    if(inicio == NULL){
        novoNoh = (NohPtr)malloc(sizeof(SNoh));
		(*novoNoh).valor = valor;
		(*novoNoh).prox = NULL;
		inicio = novoNoh;
		printf("\nPrimeiro elemento inserido na lista.\nRetornando ao menu...");
    }
    else{ // INSER��O ORDENADA
    	NohPtr nohAtual;
		nohAtual = inicio;
		if(valor < (*nohAtual).valor){ // inser��o no come�o
			novoNoh = (NohPtr)malloc(sizeof(SNoh));
			(*novoNoh).valor = valor;
			(*novoNoh).prox = nohAtual;
			inicio = novoNoh;
			printf("\nElemento inserido no in�cio da lista.\nRetornando ao menu...");
		}
		else{
			NohPtr p = inicio;
			while((*p).prox != NULL) p = (*p).prox; // sair� com p sendo o �ltimo elemento (antes de NULL)
			if(valor > (*p).valor){ // � o maior ?
				novoNoh = (NohPtr)malloc(sizeof(SNoh));
				(*novoNoh).valor = valor;
				(*novoNoh).prox = NULL;
				(*p).prox = novoNoh;
				printf("\nElemento inserido ao final da lista.\nRetornando ao menu...");
			}
			else{
				NohPtr nohAnterior;
				while(valor > (*nohAtual).valor){
					if((*nohAtual).prox != NULL){
						nohAnterior = nohAtual; //salvando o n� anterior
						nohAtual = (*nohAtual).prox; // passando o pr�ximo
					}
				} // quando sair, o valor ter� encontrado um elemento maior que ele da lista (nohAtual)
				novoNoh = (NohPtr)malloc(sizeof(SNoh));
				(*novoNoh).valor = valor; 
				(*novoNoh).prox = nohAtual; // inserindo no meio ...
				(*nohAnterior).prox = novoNoh; // ... e apontando o anterior para o novo
				printf("\nElemento inserido no meio da lista.\nRetornando ao menu...");
			}
		}
    }
    return inicio;
}

NohPtr Remocao(NohPtr inicio,int valor){
    if(inicio == NULL){
    	printf("\nNenhum elemento a ser removido.\nRetornando ao menu...");
    	return NULL;
	}
    else{
		NohPtr p,nohAtual,nohAnterior,novoNoh;
		nohAtual = inicio;
		if(valor == (*nohAtual).valor){ // remo��o de primeiro elemento
			p = (*inicio).prox; // guarda o segundo elemento em p
			free(inicio); // libera o inicio
			inicio = p; // inicio passa a ser o p
			printf("\nRemovido primeiro elemento.\nRetornando ao menu...");
			return inicio;
		}
		else{
			nohAtual = inicio;
			p = inicio;
			p = (*p).prox;
			while((*p).prox!=NULL){// para a pr�xima compara��o do if seguinte
				nohAtual = (*nohAtual).prox; // um anterior
				p = (*p).prox; // at� o �ltimo
			}
			if(valor == (*p).valor){ // ent�o remo��o do �ltimo
				(*nohAtual).prox = NULL; // "um anterior" ser� apontado para NULL
				free(p); // e a� sim poderemos liberar aquele que era igual - o �ltimo.
				printf("\nRemovido o �ltimo elemento.\nRetornando ao menu...");
			}
			else{ //se nenhum dos anteriores, ent�o � remo��o no meio
				NohPtr nohAnterior;
				nohAtual = inicio;
				while(valor != (*nohAtual).valor){
					if((*nohAtual).prox != NULL){
						nohAnterior = nohAtual; //salvando o n� anterior
						nohAtual = (*nohAtual).prox; // passando o pr�ximo
					}
				} // quando sair, o valor ter� encontrado o elemento em nohAtual
				(*nohAnterior).prox = (*nohAtual).prox;
				free(nohAtual);
				printf("\nRemovido elemento no meio da lista.\nRetornando ao menu...");
			}
		}
		
	}
	return inicio;
}
