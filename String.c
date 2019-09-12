#include <stdio.h>

int main(){
	int i, j;
	char banco[3][20], resposta;
	int posicao[3];
			
	while(resposta != 'N'){
		setbuf(stdin, NULL);
		printf("Insira uma palavra:\n");
		scanf("%s", banco[i]);
		
		setbuf(stdin, NULL);
		printf("\nDigite a gravidade:\n");
		scanf("%d", &posicao[i]);
		i++;
		
		setbuf(stdin, NULL);
		printf("\nDeseja inserir outro nome:\n");
		scanf("%c", &resposta);
	}
	
	setbuf(stdin, NULL);
	printf("Digie o indice que você deseja:\n");
	scanf("%d", &j);
	
	if(i){
		printf("%s\n", banco[j]);
		printf("%d\n", posicao[j]);
	}
	
	return 0;
}
