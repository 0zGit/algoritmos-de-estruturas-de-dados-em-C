#include <stdio.h>
#include <stdbool.h>
#include <locale.h>

/////////////////////////////////////////////////////////////////////////////////////
// PROGRAMA 3

#define TAMANHO_VET 5 //definição de tamanho inicial do vetor

void ExibeLista(bool listaComElemento,int topo,int vetor[TAMANHO_VET]);
int Push(int vetor[TAMANHO_VET],bool listaComElemento,int topo);
int Pop(bool listaComElemento,int topo,int vetor[TAMANHO_VET]);
void Consulta(bool listaComElemento,int topo,int vetor[TAMANHO_VET]);

int main(){
	setlocale(LC_ALL,"");
	
	int vetor[TAMANHO_VET]; //VETOR SETUP
	bool listaComElemento=false;
	int topo;
	MENU:
	printf("\n\n+++++++++++++++++++++++");
	printf("\n+\tEscolha uma operação ==>");
	printf("\n+\t\t0 - Encerra o programa");
	printf("\n+\t\t1 - Exibir todos os elementos da pilha");
	printf("\n+\t\t2 - Push");
	printf("\n+\t\t3 - Pop");
	printf("\n+\t\t4 - Consultar último elemento de remoção");
	printf("\n>> ");
	int escolhaMenu;
	scanf("%d",&escolhaMenu);
	
	switch(escolhaMenu){
		case 0:{
			printf("\n\nFechando programa...");
			return 0;
			break;
		} 
		case 1:{
			ExibeLista(listaComElemento,topo,vetor);
			break;
		}
		case 2:{
			topo = Push(vetor,listaComElemento,topo);
			listaComElemento=true;
			break;
		}
		case 3:{
			topo = Pop(listaComElemento,topo,vetor);
			if(topo == -1) listaComElemento = false;
			break;
		}
		case 4:{
			Consulta(listaComElemento,topo,vetor);
			break;
		}
		default:{
			printf("\nInválido. Retornando ao Menu...");
			break;
		}
	}
	goto MENU;
}

void ExibeLista(bool listaComElemento,int topo,int vetor[TAMANHO_VET]){
	int i=0;
	if(listaComElemento == false){
		printf("\n\nFavor preencher lista primeiro.");
		printf("\nRetornando ao Menu...\n\n");
	}
	else{
		for(i=0;i<=topo;i++) printf("\nVetor[%d]=%d",i,vetor[i]);
		printf("\nVetor exibido. Voltando ao Menu...");
	}
}


int Push(int vetor[TAMANHO_VET],bool listaComElemento,int topo){
	int elemento;
	
	if(listaComElemento == false){
		topo = 0;
		printf("\nInserir >> vetor[%d]= ",topo);
		scanf("%d",&elemento);
		vetor[topo] = elemento;
	}
	else{
		if(topo+1 == TAMANHO_VET) printf("\nVetor totalmente preenchido.\nRetornando ao menu...");
		else{
			topo++;
			printf("\nInserir >> vetor[%d]= ",topo);
			scanf("%d",&elemento);
			vetor[topo] = elemento;
			printf("\nElemento inserido.\nRetornando ao menu...");
		}
	}
	return topo;
}


int Pop(bool listaComElemento,int topo,int vetor[TAMANHO_VET]){
	if(listaComElemento == false){
		printf("\n\nFavor preencher lista primeiro.");
		printf("\nRetornando ao Menu...\n\n");
	}
	else{
		printf("\nElemento vetor[%d]=%d removido. Retornando ao Menu....",topo,vetor[topo]);
		topo--;
		return topo;
	}
}
void Consulta(bool listaComElemento,int topo,int vetor[TAMANHO_VET]){
	if(listaComElemento == false){
		printf("\n\nFavor preencher lista primeiro.");
		printf("\nRetornando ao Menu...\n\n");
	}
	else printf("\nO elemento que pode ser removido é o vetor[%d]=%d\nVoltando ao Menu...",topo,vetor[topo]);
}
