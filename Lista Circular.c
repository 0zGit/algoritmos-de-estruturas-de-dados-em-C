#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

/////////////////////////////////////////////////////////////////////////////////////
// PROGRAMA 5

typedef struct SNoh{
    int valor;
    struct SNoh *prox;
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
	printf("\n+\t\t1 - Exibir lista circular");
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
				NohPtr p=inicio;
				if((*p).valor == valor){
					printf("\nIniciando remo��o.");
					inicio = Remocao(inicio,valor);
					break;
				}
				else{
					while((*p).valor != valor){
						p = (*p).prox;
						if((*p).valor == valor){
							printf("\nIniciando remo��o.");
							inicio = Remocao(inicio,valor);
							break;
						}
						else if(p == inicio){
							printf("\nElemento n�o encontrado.");
							break;
						}	
					}
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
    printf("\nImprimindo lista circular:\n");
    do{
    	printf("%d\t",(*p).valor);
    	p = (*p).prox;
	}while((*p).prox != (*inicio).prox); // QUANDO O PR�XIMO ELEMENTO FOR DIFERENTE DO PR�XIMO DO IN�CIO. kjkjkjk
}


NohPtr Insercao(NohPtr inicio,int valor){
	NohPtr p,novoNoh;
	
	if(inicio == NULL){
    	novoNoh = (NohPtr)malloc(sizeof(SNoh));
		(*novoNoh).valor = valor;
		(*novoNoh).prox = novoNoh;
		inicio = novoNoh;
		printf("\nPrimeiro elemento inserido.\nRetornando ao menu...");
		return inicio;
	}
	else{
		p = inicio;
		while((*p).prox != inicio) // PERCORRE AT� O FINAL DA LISTA
			p = (*p).prox;
		if(valor > (*p).valor){ // VALOR � O MAIOR DO QUE O �LTIMO ELEMENTO DA LISTA ?
			novoNoh = (NohPtr)malloc(sizeof(SNoh));
			(*novoNoh).valor = valor;
			(*novoNoh).prox = inicio; // lista circular
			(*p).prox = novoNoh; // o anterior passa a ter como pr�ximo o novoNoh
			printf("\nElemento inserido ao final da lista.\nRetornando ao menu...");
		}
		else{ // DO CONTR�RIO...
			p = inicio; // VOLTANDO AO PRIMEIRO ELEMENTO
			if(valor < (*p).valor){ // VALOR � O MENOR DA LISTA? (ENQUEUE)
				novoNoh = (NohPtr)malloc(sizeof(SNoh));
				(*novoNoh).valor = valor;
				(*novoNoh).prox = p;
				NohPtr aux;
				aux = inicio; // AGORA PRECISA PERCORRER AT� O FINAL ...
				while((*aux).prox != inicio)
					aux = (*aux).prox;
				(*aux).prox = novoNoh; // ... INDICAR QUE O PR�XIMO � O NOVO ELEMENTO ...
				inicio = novoNoh; // ... E ATUALIZAR O INICIO
				printf("\nElemento inserido ao in�cio da lista.\nRetornando ao menu...");
			}
			else{ // N�O � O MENOR NEM O MAIOR DA LISTA
				NohPtr nohAtual,nohAnterior;
				nohAtual = inicio;
				while(valor > (*nohAtual).valor){
					if((*nohAtual).prox != inicio){
						nohAnterior = nohAtual; //salvando o n� anterior
						nohAtual = (*nohAtual).prox; // passando o pr�ximo
					}
				} // quando sair, o valor ter� encontrado  um elemento maior que ele da lista
				novoNoh = (NohPtr)malloc(sizeof(SNoh));
				(*novoNoh).valor = valor;
				(*novoNoh).prox = nohAtual; // inserindo no meio ...
				(*nohAnterior).prox = novoNoh; // ... e apontando o anterior para o novo
				printf("\nElemento inserido ao meio da lista.\nRetornando ao menu...");
			}
		}
	}
    return inicio;
}


NohPtr Remocao(NohPtr inicio,int valor){
	if((*inicio).prox == inicio){
		free(inicio);
		inicio = NULL;
		printf("\nRemovido �nico elemento da lista.\nRetornando ao menu...");
	}
	else{
		NohPtr nohAtual;
		nohAtual = inicio;
		if((*inicio).valor == valor){ // � o primeiro?
			nohAtual = (*nohAtual).prox;
			free(inicio);
			inicio = nohAtual;
			(*nohAtual).prox = inicio;
			printf("\nRemovido primeiro elemento da lista.\nRetornando ao menu..."); // YEEEEEEEEEEEEEEEEEEEEESSSSSSSSSSSSSSSSSSSSSSSSSSSS
		}
		else{
			NohPtr nohAnterior;
			while((*nohAtual).prox != inicio){
				nohAnterior = nohAtual; //salvando o n� anterior
				nohAtual = (*nohAtual).prox; // passando o pr�ximo
			} // quando sair, o nohAtual ser� o �ltimo (antes do inicio)
			if((*nohAtual).valor == valor){ // � o �ltimo?
				free(nohAtual); // liberamos o �ltimo
				(*nohAnterior).prox = inicio; // e o anterior, agora �ltimo, ser� apontado para o come�o
				printf("\nRemovido �ltimo elemento da lista.\nRetornando ao menu...");
			}
			else{ // � remo��o no meio
				nohAtual = inicio;
				while(valor != (*nohAtual).valor){
					if((*nohAtual).prox != inicio){
						nohAnterior = nohAtual; //salvando o n� anterior
						nohAtual = (*nohAtual).prox; // passando o pr�ximo
					}
				} // quando sair, o valor ter� encontrado o elemento igual a ele na lista
				(*nohAnterior).prox = (*nohAtual).prox;
				free(nohAtual);
				printf("\nElemento removido ao meio da lista.\nRetornando ao menu...");
			}
		}
	}
	return inicio;
}
