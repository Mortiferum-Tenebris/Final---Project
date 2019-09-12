#include <stdio.h>
#include <locale.h>

int main(){
	int i = 0, j = 0, cont;
	int valores[3];
	int aux1 = 0, aux2 = 0;
	char resposta, nomes[3][20];
	char caractAux1 [20], caractAux2[20];

	setlocale(LC_ALL, "Portuguese");
	
	for(cont = 0; cont < 3; cont++){
		valores[cont] = '\0';
	}
	
	while(resposta != 'N'){
		
		setbuf(stdin, NULL);
		printf("Insira valores:\n");
		scanf("%d", &valores[i]);
		
		printf("Insira uma palavra:\n");
		scanf("%s", nomes[i]);
		i++;
		
		setbuf(stdin, NULL);
		printf("Deseja inserir outro valor:\n");
		scanf("%c", &resposta);
		
	}
	
	for(i = 0; i < 3; i++){
		j = i + 1;
		
		while(j < 3){
			if(valores[i] < valores[j]){
				aux1 = valores[j];
				aux2 = valores[i];
				valores[i] = aux1;
				valores[j] = aux2;
				
				strcpy(caractAux1, nomes[j]);
				strcpy(caractAux2, nomes[i]);
				strcpy(nomes[i], caractAux1);
				strcpy(nomes[j], caractAux2);
				
			}
		
			else{
				aux1 = valores[j];
				aux2 = valores[i];
				valores[i] = aux2;
				valores[j] = aux1;
			}
			
			j++;
		}
		
		if(valores[i] != 0){
			printf("%d\n", valores[i]);
			printf("%s\n", nomes[i]);
		}
	}
	
	
	return 0;
}
