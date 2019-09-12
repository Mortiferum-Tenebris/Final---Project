#include <stdio.h>
#include <locale.h>
#include <windows.h>

extern void inicializa();
extern int fila_vazia();
extern void insere_fila();
extern void retira_fila();
extern void imprime_fila();

char fila[3][50];
int fim = 0;
int inicio = -1;
int nElementos = 0;

int main(){
	char resposta[4];
	int i;
	
	setlocale(LC_ALL, "Portuguese");
	
	inicializa();
	
	for(i = 0; i <= 2; i++){
		
		setbuf(stdin, NULL);
		printf("Deseja inserir um elemento?\n");
		gets(resposta);

		
		if(!stricmp(resposta, "Sim")){
			insere_fila();
		}
	
		setbuf(stdin, NULL);
		printf("Deseja remover um elemento?\n");
		gets(resposta);
	
		if(!stricmp(resposta, "Sim")){
			retira_fila();
		}
	}
	
	imprime_fila();
	
	return 0;
}

void inicializa(){
	int i, j;
	
	for(i = 0; i < 3; i++){
		for(j = 0; j < 50; j++){
			fila [i][j] = '\0';	
		}
	}
}

int fila_vazia(){
	
	if(nElementos < 3){
		return 1;
	}
	
	else if(nElementos == 3){
		nElementos = 0;
		return 0;
	}
}

void insere_fila(){
	inicio++;
	
	if(inicio == 3){
		inicio = 0;
	}
	
	printf("Digite a palavra a ser inserido:\n");
	scanf("%s", &fila[inicio]);
	
	nElementos++;
}

void retira_fila(){
	int i;
	
	for(i = 0; i < 50; i++){
		fila[fim][i] = '\0';	
	}
	
	if(fim == 3){
		fim = 0;
	}
	
	fim++;
}

void imprime_fila(){
	int i;
	
	for(i = 0; i < 3; i++){
		printf("%s\n", fila[i]);
	}
}
