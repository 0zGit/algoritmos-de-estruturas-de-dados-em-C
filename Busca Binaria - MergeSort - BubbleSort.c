#include <stdio.h>
#include <stdbool.h>
#include <locale.h>

/////////////////////////////////////////////////////////////////////////////////////
// PROGRAMA 1 (Bug ao remover todos os elementos da lista e MergeSort não funciona)

#define TAMANHO_VET 5

void ExibeLista(bool listaComElemento,int vetorMax,int vetor[vetorMax]);
int InsereElemento(int vetorMax, int vetor[vetorMax],bool listaComElemento,bool listaCheia);
void TrocaBubbleSort(int vetorMax, int vetor[vetorMax],int i);
void BubbleSort(int vetorMax,int vetor[vetorMax]);
void Merge(int esquerda,int meioEsquerda,int meioDireita,int direita,int vetorMax, int vetor[vetorMax]);
void Sort(int esquerda,int direita,int vetorMax, int vetor[vetorMax]);
void OrdenaLista(int vetorMax, int vetor[vetorMax]);
int BuscaBinaria(int elemento,int vetorMax, int vetor[vetorMax],int inf,int meio,int sup);
void BuscaElemento(int vetorMax,int vetor[vetorMax],int elemento);
int RemoveElemento(int vetorMax,int vetor[vetorMax],int elemento,bool listaCheia,bool listaComElemento);

int main(){
	setlocale(LC_ALL,"");
	
	bool listaComElemento=false,listaOrdenada=false,listaCheia=false;
	int vetorMax=TAMANHO_VET,vetor[vetorMax];
	int elemento;
	MENU:
	printf("\n+++++++++++++++++++++++");
	printf("\n+\tEscolha uma operação ==>");
	printf("\n+\t\t0 - Encerra o programa");
	printf("\n+\t\t1 - Exibir todos os elementos da lista");
	printf("\n+\t\t2 - Inserir elemento no início da lista");
	printf("\n+\t\t3 - Remover elemento");
	printf("\n+\t\t4 - Buscar elemento");
	printf("\n+\t\t5 - Ordenar lista");
	printf("\n>> ");
	int escolhaMenu;
	scanf("%d",&escolhaMenu);
	
	switch(escolhaMenu){
		case 0:{
			printf("\n\nFechando programa...");
			return 0;
		} 
		case 1:{
			if(vetorMax == -1) printf("\nFavor preencher lista primeiro.");
			else ExibeLista(listaComElemento,vetorMax,vetor);
			break;
		}
		case 2:{
			vetorMax = InsereElemento(vetorMax,vetor,listaComElemento,listaCheia);
			listaComElemento=true;
			listaOrdenada=false;
			break;
		}
		case 3:{
			if(listaComElemento!=true) printf("\n\nFavor preencher lista primeiro.\nRetornando ao menu...");
			else{
				printf("\n\nEscolha o elemento que deseja ser removido: ");
				scanf("%d",&elemento);
				vetorMax = RemoveElemento(vetorMax,vetor,elemento,listaCheia,listaComElemento);
			}
			break;
		}
		case 4:{
			if(listaOrdenada!=true || listaComElemento!=true) printf("\n\nFavor ordenar e/ou inserir lista primeiro.\nRetornando ao menu...");
			else{
				printf("\n\nEscolha o elemento que deseja ser buscado: ");
				scanf("%d",&elemento);
				BuscaElemento(vetorMax,vetor,elemento);
			}
			break;
		}
		case 5:{
			if(listaComElemento!=true) printf("\n\nFavor preencher lista primeiro.\nRetornando ao menu...");
			else{
				OrdenaLista(vetorMax,vetor);
				listaOrdenada=true;
			}
			break;
		}
		default:{
			printf("\nInválido. Retornando ao Menu...");
			break;
		}
	}
	goto MENU;
}

void ExibeLista(bool listaComElemento,int vetorMax,int vetor[vetorMax]){
	int i;
	if(listaComElemento == false) printf("\n\nFavor preencher lista primeiro.\nRetornando ao menu...");
	else{
		for(i=0;i<vetorMax;i++) printf("\nVetor[%d]=%d",i,vetor[i]);
		printf("\nVetor exibido. Voltando ao Menu...");
	}
	
	return;
}


int InsereElemento(int vetorMax, int vetor[vetorMax],bool listaComElemento,bool listaCheia){
	int i,elemento;
	
	if(listaComElemento == true && listaCheia == false){
		for(i=vetorMax;i<TAMANHO_VET;i++){
			printf("Inserir >> vetor[%d]= ",i);
			scanf("%d",&elemento);
			vetor[i] = elemento;
			vetorMax++;
		}
	}
	else if(listaComElemento == false){
		for(i=0;i<vetorMax;i++){
			printf("Inserir >> vetor[%d]= ",i);
			scanf("%d",&elemento);
			vetor[i] = elemento;
		}
	}
	printf("\nLista completamente preenchida.\nRetornando ao menu...");
	listaCheia = true;
	return vetorMax;
}


void TrocaBubbleSort(int vetorMax, int vetor[vetorMax],int i){
	int aux;
	aux = vetor[i-1];
	vetor[i-1] = vetor[i];
	vetor[i] = aux;
	
	return;
}
void BubbleSort(int vetorMax,int vetor[vetorMax]){
	int i;
	bool trocou = true;
	
	while(trocou == true){
		trocou = false;
		for(i=1;i<vetorMax;i++){
			if(vetor[i-1] > vetor[i]){
				TrocaBubbleSort(vetorMax,vetor,i);
				trocou = true;
			}
		}
	}
	
	return;
}
void Merge(int esquerda,int meioEsquerda,int meioDireita,int direita,int vetorMax,int vetor[vetorMax]){
	int indEsq=esquerda,indDir=meioDireita,indexComb=0;
	int i,aux[vetorMax];
	
	
	while(indEsq<=meioEsquerda && indDir<=direita){
		if(vetor[indEsq] <= vetor[indDir]){
			aux[indexComb] = vetor[indEsq];
			indEsq++;
		}
		else{
			aux[indexComb] = vetor[indDir];
			indDir++;
		}
		indexComb++;
	}
	while(indEsq<=meioEsquerda){
		aux[indexComb] = vetor[indEsq];
		indEsq++;
		indexComb++;
	}
	while(indDir<=direita){
		aux[indexComb] = vetor[indDir];
		indDir++;
		indexComb++;
	}
	
	for(i=0;i<vetorMax;i++) vetor[i] = aux[i];
}
void Sort(int esquerda,int direita,int vetorMax,int vetor[vetorMax]){
	int meio1,meio2;
	
	if(esquerda == direita) return;
	if(esquerda < direita){
		meio1 = (esquerda+direita)/2;
		meio2 = meio1+1;
		Sort(esquerda,meio1,vetorMax,vetor);
		Sort(meio2,direita,vetorMax,vetor);
		Merge(esquerda,meio1,meio2,direita,vetorMax,vetor);
	}
}


void OrdenaLista(int vetorMax,int vetor[vetorMax]){
	int esquerda=0,direita=vetorMax-1;
	int escolhaAlg;
	printf("\n\nDeseja utilizar qual Algoritmo de Ordenação?");
	printf("\n\t0 - BubbleSort O(n²)");
	printf("\n\t1 - MergeSort O(nlog2n)");
	printf("\n>> ");
	scanf("%d",&escolhaAlg);
	escolhaAlg == 0 ? BubbleSort(vetorMax,vetor) : Sort(esquerda,direita,vetorMax,vetor);
	switch(escolhaAlg){
		case 0:{
			printf("\nLista ordenada via BubbleSort. Retornando ao Menu...");
			break;
		}
		case 1:{
			printf("\nLista ordenada via MergeSort. Retornando ao Menu...");
			break;
		}
	}
}
int BuscaBinaria(int elemento,int vetorMax,int vetor[vetorMax],int inf,int meio,int sup){
	while(inf<=sup){
		meio = (inf+sup)/2;
		if(elemento == vetor[meio]) return meio;
		else if(elemento > vetor[meio]) BuscaBinaria(elemento,vetorMax,vetor,inf=meio+1,meio,sup);
		else if(elemento < vetor[meio]) BuscaBinaria(elemento,vetorMax,vetor,inf,meio,sup=meio-1);
	}
	return -1;
}
void BuscaElemento(int vetorMax,int vetor[vetorMax],int elemento){
	int sup=vetorMax,inf=0,meio=0;
	int retorno = BuscaBinaria(elemento,vetorMax,vetor,inf,meio,sup);
	if(retorno == -1) printf("\nElemento não encontrado.\nRetornando ao menu...");
	else printf("\nElemento encontrado em: vetor[%d]=%d",retorno,vetor[retorno]);
	return;
}
int RemoveElemento(int vetorMax,int vetor[vetorMax],int elemento,bool listaCheia,bool listaComElemento){
	int i=0,k;
	
	while(i <= vetorMax){
		if(vetor[i] == elemento){
			for(k=i;k<vetorMax;k++) vetor[k] = vetor[k+1];
			vetorMax--;
			listaCheia = false;
			if(vetorMax == -1) listaComElemento = false;
			printf("\nElemento removido. Retornando ao Menu...");
			return vetorMax;
		}
		i++;
	}
	printf("\nNenhum elemento a ser removido. Retornando ao Menu...");
	return vetorMax;
}
