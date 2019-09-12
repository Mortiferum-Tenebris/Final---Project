/****
 * 
 * T�tulo: Programa de Triagem M�dica
 *
 * Autores: Alexandre Bezerra de Lima
 *			Larissa Gomes Marinho
 *			L�via No�mia Morais Rocha
 *			Ryann Carlos de Arruda Quintino
 *			Victor Henrique Feliz Brasil
 *
 * Data da cria��o: 05/06/2019
 * �ltima modifica��o: 12/09/2019
 *
 * Descri��o: O programa realiza o cadastro de funcion�rios, cadastro pacientes, acessa os dados dos pacientes, cadastrar sintomas do paciente,...(ADICIONAR CONTINUA��O)
 *
 ****/


#ifdef __unix__
	#include <stdio.h>
	#include <locale.h>
	#include <string.h>
	#include <stdlib.h>
	#include <unistd.h> /*Serve para que se possa utilizar a fun��o "sleep()" do sistema Unix/Linux*/
	
#elif defined(_WIN32) || defined(WIN32)
	
	#define OS_Windows 
	
	#include <stdio.h>
	#include <locale.h>
	#include <string.h>
	#include <stdlib.h>
	#include <windows.h> /*Serve para que se possa utiliar a fun��o "Sleep()" do sistema Windows */

#endif

#define MAX 2

extern void TelaLogin();
extern int  LeituraAcesso();
extern void EscolhaAdm();
extern void EscolhaFuncionario();
extern void InicializaFuncionarios();
extern int  ProcurarVazio();
extern void CadastroFuncionario();
extern void ArmazenaLoginFuncionario();
extern void ArmazenaDadosFun();
extern void Cadastro(char nome[], int idade, int registro, char SexoUser[], char arquivo[]);
extern void CadastrarPaciente(); 
extern void ArquivoPaciente();
extern void CadastraSintomas();
extern int  Triagem(const char SintomasPaciente[][30]);
extern int  CalculaClassificacao(int contAzul, int contVerde, int contAmarelo, int contVermelho);
extern int VerificacaoEspecial(int ContAzul, int ContVerde, int ContAmarelo, int ContVermelho);
extern void LimpaBuffer();


char gLoginSistema[30], gSenhaSistema[16];   /*As fun��es "main()" e "leitura_acesso()" necessitam delas*/
int  gsituacao = 0; 					     /*Usada para verificar a situa��o do banco de dados.*/
char gextensao[] = "_login_senha.txt";     	 /*Passa a extens�o para o salvamento do login do funcion�rio e para que ele possa se logar*/
char gresposta[4]; 							 /*Utilizada pelas fun��es cadastrar_paciente() e arquivo_paciente() para verificar se o usu�rio deseja fazer outra opera��o*/
int  i = 0; 			                     /*Utilizada para verificar se a mensagem inicial foi exibida, de modo que quando retornar a tela de login, n�o exiba novamente*/
int  p = 0;									 /*Utilizado para controlar a quantidade de funcion�arios cadastrados.*/


int main(){
	char LoginMestre[] = "ryann.arruda", SenhaMestre[] = "diretor";
	
	setlocale(LC_ALL, "Portuguese");											/*Coloca a acentua��o do portugu�s na sa�da */		
	
	if(i != 1){
		printf("Seja bem-vindo ao nosso sistema.\n\n");
		
		#ifdef OS_Windows
			Sleep(800);		/*Coloca um temporizador (levando em considera��o o sistema Windows)*/
			system("cls");
	
		#else
			sleep(8);		/*Coloca um temporizador (levando em considera��o o sistema Linux/Unix)*/
			system("clear");
	
		#endif
	}
	
	printf("Login:\n");
	scanf("%29[^\n]s", gLoginSistema);
	LimpaBuffer();
	
	printf("\nSenha:\n");
	scanf("%15[^\n]s", gSenhaSistema);
	LimpaBuffer();
	
	#ifdef OS_Windows
	
		system("cls");
	
	#else
		
		system("clear");
	
	#endif
	
	if((strcmp(gLoginSistema, LoginMestre) == 0) && (strcmp(gSenhaSistema, SenhaMestre) == 0)){
		i = 1;
		EscolhaAdm();
	}
	
	else if(LeituraAcesso() == 1){
		i = 1;
		EscolhaFuncionario();
	}
	
	else {
		printf("Login ou senha est�o incorretas.");
		i = 1;
		
		#ifdef OS_Windows
			Sleep(800);
			system("cls");
	
		#else
			sleep(8);
			system("clear");
	
		#endif
		
		main();
	}
	
	return 0;
}

/****
 * Descri��o: Estrutura que possui os dados que s�o requisitados ao funcion�rio.
 *
 ****/
typedef struct {
	char 		 NomeFuncionario[51];
	char 		 SexoFuncionario[11];
	char 		 EnderecoFuncionario[50];
	unsigned int IdadeFuncionario;
	char 		 LoginUser[30];
	char 		 SenhaUser[16];
}tfuncionario;

tfuncionario gmember[MAX];   /*Matriz global do tipo "tfuncion�rio" que ir� armazenar os dados dos funcion�rios.*/


/****
 * Descri��o: Verifica o login do funcion�rio de acordo com os dados salvos em arquivo de login e senha, respectivamente.
 * 
 * Par�metros: Nenhum
 *
 * Valor de retorno: A fun��o retorna 1 para que quando o "adm" ou o funcion�rio sa�a do sistema para a tela de login n�o exiba a mensagem de "Bem-Vindos" o mesmo
 *					 ocorre para o caso de ambos errarem seus dados de acesso.
 ****/
 
int LeituraAcesso(){  
	char LeituraLogin[30], LeituraSenha[30];
	char PrimeiroArmazenamento[30], SegundoArmazenamento[30], login[30];
	
	strcpy(login, gLoginSistema);
	strcat(login, gextensao);
	
	FILE *informacoes_login;
	
	informacoes_login = fopen(login, "r");
	
	while(fscanf(informacoes_login, "%s %s", LeituraLogin, LeituraSenha) != EOF){
		
		strcpy(PrimeiroArmazenamento, LeituraLogin);
		strcpy(SegundoArmazenamento, LeituraSenha);
		
		if((strcmp(PrimeiroArmazenamento, gLoginSistema) == 0) && (strcmp(SegundoArmazenamento, gSenhaSistema) == 0)){
			fclose(informacoes_login);
			return 1;
		}
	}
}
 
void EscolhaAdm(){ 																		
	int  opcao = 0;
			
	printf(" 1 - Cadastrar Funcion�rio\t");
	printf(" 2 - Sair do Sistema\t\n\n");
	
	printf("Insira o n�mero correspodente a op��o que voc� deseja acessar:\n");
	scanf("%d", &opcao);
	LimpaBuffer();
	
	#ifdef OS_Windows
	
		system("cls");
	
	#else
		
		system("clear");
	
	#endif
		
	switch (opcao){
		case 1:
			CadastroFuncionario();
			break;
		
		case 2:
			main();
			break;
		
		default:
			EscolhaAdm();
			break;
	}
}

void EscolhaFuncionario(){ 															
	int  opcao = 0;
			
	printf(" 1 - Cadastrar Paciente\t\n");
	printf(" 2 - Acessar Dados do Paciente\t\n");							
	printf(" 3 - Cadastrar Sintomas do Paciente\t\n"); 	
	printf(" 4 - Sair do Sistema\t\n");										
	
	printf("Insira o n�mero correspodente a op��o que voc� deseja acessar:\n");
	scanf("%d", &opcao);
	LimpaBuffer();
	
	#ifdef OS_Windows
	
		system("cls");
	
	#else
		
		system("clear");
	
	#endif
		
	switch (opcao){
		case 1:
			CadastrarPaciente();
			break;
		
		case 2:
			ArquivoPaciente();
			break;
			
		case 3:
			CadastraSintomas();
			break;
			
		case 4:
			main();
			break;
		
		default:
			EscolhaFuncionario();
			break;
	}
}

/****
 * Descri��o: Inicializa a matriz "gmember" do tipo struct, a qual ir� armazenar os dados do funcion�rio, com o primeiro elemento nulo (\0).
 *
 * Par�metros: Nenhum.
 *
 * Valor de Retorno: Nenhum.
 *
 ****/
void InicializaFuncionarios(){ 
	int t;
	
	for(t = 0; t < MAX; t++){
		gmember[MAX].NomeFuncionario[t] = '\0';
	}
}

/****
 * Descri��o: Procura algum espa�o vazio na matriz do tipo struct a fim de armazenar novos funcion�rios.
 *
 * Par�metros: Nenhum.
 *
 * Valor de retorno: Retorna um valor inteiro que ir� servir para verificar a situa��o da quantidade de funcion�rios que j� foi preenchida.
 *
 ****/
int ProcurarVazio(){

	if(p < MAX){
		return p;
	}
	
	else if(p == MAX){		
		return -1;
	}
}

void CadastroFuncionario(){   		
	
	InicializaFuncionarios();   
	
	if(ProcurarVazio() == -1){
		printf("Banco de dados cheio!");

		#ifdef OS_Windows
			Sleep(800);
			system("cls");
	
		#else
			sleep(5);
			system("clear");
	
		#endif
		
		EscolhaAdm();
	}
	
	printf("Insira o nome do funcion�rio:\n");
	scanf("%50[^\n]s", gmember[gsituacao].NomeFuncionario);
	LimpaBuffer();
	
	printf("\nInsira o sexo do funcion�rio:\n");
	scanf("%10s", gmember[gsituacao].SexoFuncionario);
	LimpaBuffer();
	
	printf("\nInsira o endere�o do funcion�rio:\n");
	scanf("%49[^\n]s", gmember[gsituacao].EnderecoFuncionario);
	LimpaBuffer();
	
	printf("\nInsira a idade do funcion�rio:\n");
	scanf("%d", &gmember[gsituacao].IdadeFuncionario);
	LimpaBuffer();
	
	printf("\nInsira o login do funcion�rio:\n");
	scanf("%29s", gmember[gsituacao].LoginUser);
	LimpaBuffer();
	
	printf("\nInsira a senha do funcion�rio:\n");
	scanf("%15s", gmember[gsituacao].SenhaUser);
	LimpaBuffer();

	#ifdef OS_Windows
		system("cls");
	
	#else
		system("clear");
	
	#endif

	ArmazenaLoginFuncionario();
	
	ArmazenaDadosFun();
	
	ProcurarVazio();
	
	p++; 
	
	EscolhaAdm();
	
}

/****
 * Descri��o: Armazena os dados de login e senha dos funcion�rios
 *
 * Par�metros: Nenhum
 *
 * Valor de retorno: Nenhum
 *
 ****/
void ArmazenaLoginFuncionario(){ 
	char ArmazenaNome[20];
	
	strcpy(ArmazenaNome, gmember[gsituacao].LoginUser);
	strcat(ArmazenaNome, gextensao);						/*Passa a exters�o "_login_senha.txt" para o nome do funcion�rio*/
	
	FILE *informacoes_login;
	
	informacoes_login = fopen(ArmazenaNome, "w");
	
	if(informacoes_login == NULL){
		printf("N�o foi poss�vel salvar os dados de login e senha do funcion�rio, por favor, tente novamente!");
		gmember[gsituacao].NomeFuncionario[0] = '\0';

		#ifdef OS_Windows
			Sleep(800);
			system("cls");
	
		#else
			sleep(5);
			system("clear");
	
		#endif
		
		EscolhaAdm();
	}
	
	fprintf(informacoes_login, "%s\n", gmember[gsituacao].LoginUser);
	fprintf(informacoes_login, "%s", gmember[gsituacao].SenhaUser);
	fclose(informacoes_login);
}

/****
 * Descri��o: Armazena os demais dados dos funcion�rios, como: nome, sexo, endere�o e idade
 * 
 * Par�metros: Nenhum
 *
 * Valor de retorno: Nenhum
 *
 ****/
void ArmazenaDadosFun(){
	char ArmazenaNome[30];
	
	FILE *dados_func;
	
	strcpy(ArmazenaNome, gmember[gsituacao].NomeFuncionario);
	strcat(ArmazenaNome, ".txt");
	
	dados_func = fopen(ArmazenaNome, "w");
	
	if(dados_func == NULL){
		printf("N�o foi poss�vel acessar o banco de dados para o armazenamento das informa��es! Entre em contato com o suporte.");

		#ifdef OS_Windows
			Sleep(800);
			system("cls");
	
		#else
			sleep(5);
			system("clear");
	
		#endif
		
		EscolhaAdm();
	}
	
	fprintf(dados_func, "\t\tDADOS DO FUNCION�RIO\t\t\n\n");
	fprintf(dados_func, "NOME = %s\n", gmember[gsituacao].NomeFuncionario);
	fprintf(dados_func, "SEXO = %s\n", gmember[gsituacao].SexoFuncionario);
	fprintf(dados_func, "ENDERE�O = %s\n", gmember[gsituacao].EnderecoFuncionario);
	fprintf(dados_func, "IDADE = %d\n", gmember[gsituacao].IdadeFuncionario);
	
	fclose(dados_func);
}

/****
 * Descri��o: Armazena os dados dos pacientes (nome, idade, registro, sexo) cadastrados no sistema.
 *
 * Par�metros: Entrada: nome - string que ir� armazenar os nomes dos pacientes,
 *						idade - inteiro que armazenar� a idade dos pacientes,
 * 						registro - inteiro que armazenar� o registro dos pacientes,
 *						sexo_user - string que armazenar� o sexo dos pacientes,
 *						arquivo - string que passa a concatena��o do nome do paciente com a extens�o ".doc" localizada no bloco "cadastrar_paciente()".
 *
 * Valor de retorno: Nenhum
 *
 ****/
void Cadastro(char nome[], int idade, int registro, char SexoUser[], char arquivo[]){   
	
	FILE *dados;
	
	if(dados == NULL){
		printf("N�o foi poss�vel armazenar os dados do paciente! Por favor, tente novamente.");
		EscolhaFuncionario();
	}

	dados = fopen (arquivo, "w");
	fprintf(dados, "\t\tFicha do Paciente\t\t\n\n");
	fprintf(dados, "Nome: %s", nome);
	fprintf(dados, "\n\nIdade: %d", idade);
	fprintf(dados, "\n\nRegistro: %d", registro);
	fprintf(dados, "\n\nSexo: %s", SexoUser);
	fclose(dados);	
}

void CadastrarPaciente(){                   
		int idade = 0, NumeroRegistro = 0;
		char nome[50], SexoUser [11];
		char arquivo[50], extensao [5] = ".doc";									/* Passa extenss�o ".doc" para o arquivo poder ser criado*/
	
		printf ("Insira os seguintes dados para realizar o cadastro.\n\n");

		#ifdef OS_Windows
			Sleep(1000);
			system("cls");
	
		#else
			sleep(1);
			system("clear");
	
		#endif
		
		printf("Nome:");
		scanf("%49[^\n]s", nome);
		LimpaBuffer();
		
		printf("\n\nIdade:");
		scanf ("%d" , &idade);
		LimpaBuffer();
		
		if(idade < 0 ){
			printf("Idade n�o reconhecida ou inv�lida, tente novamente com uma idade v�lida.");
			    	
		#ifdef OS_Windows
			system("cls");
	
		#else
			system("clear");
	
		#endif
			CadastrarPaciente();
		}
		
		printf("\n\nRegistro:");
		scanf ("%d" , &NumeroRegistro);
		LimpaBuffer();
		
		if(NumeroRegistro < 0){
			printf("Registro n�o reconhecindo ou inv�lido, tente novamente com um registro v�lido.");
    	
			#ifdef OS_Windows
				system("cls");
	
			#else
				system("clear");
	
			#endif
		
			CadastrarPaciente();			
		}
		
		printf("\n\nSexo:");
		scanf ("%10[^\n]s" , &SexoUser);
		LimpaBuffer();
		
		if(!stricmp(SexoUser, "Masculino")){
			strcpy(arquivo, nome);											/*Copia o nome do paciente e passa para a string "arquivo"*/
			strcat(arquivo, extensao);										/*Concatena o nome do paciente com a string arquivo*/
			Cadastro(nome, idade, NumeroRegistro, SexoUser, arquivo);			
		}
		
		else if(!stricmp(SexoUser, "Feminino")){
			strcpy(arquivo, nome);											/*Copia o nome do paciente e passa para a string "arquivo"*/
			strcat(arquivo, extensao);										/*Concatena o nome do paciente com a string arquivo*/
			Cadastro(nome, idade, NumeroRegistro, SexoUser, arquivo);
		}
		
		else{
			printf("Sexo inv�lido!");
		}
		
		#ifdef OS_Windows
			system("cls");
	
		#else
			system("clear");
	
		#endif
		
		printf("\nDeseja cadastrar outro paciente?\n");
		scanf("%3[^\n]s", gresposta);
		LimpaBuffer();
		
		if(!stricmp(gresposta, "Sim")){
			
			#ifdef OS_Windows
				system("cls");
	
			#else
				system("clear");
	
			#endif
			
			CadastrarPaciente();
		}
		
		else{
			
			#ifdef OS_Windows
				system("cls");
	
			#else
				system("clear");
	
			#endif
			
			EscolhaFuncionario();
		}
}

/****
 * Descri��o: Permite acessar os dados do paciente como: nome, idade, registro e sexo.
 *
 * Par�metros: Nenhum.
 *
 * Valor de retorno: Nenhum.
 *
 ****/
void ArquivoPaciente(){
    char nome[50], ler[100];
    char extensao [5] = ".doc";
    
    printf("Digite o nome do paciente:\n");
    scanf("%[A-Za-z 0-9]s", &nome);
	LimpaBuffer();			
    
    strcat(nome, extensao);
 	
	#ifdef OS_Windows
		system("cls");
	
	#else
		system("clear");
	
	#endif

    FILE *file;

    file = fopen(nome, "r");

    if(file == NULL){
        printf("Nao foi possivel abrir o arquivo.\n");
        
		#ifdef OS_Windows
			Sleep(1000);
			system("cls");
	
		#else
			sleep(1);
			system("clear");
	
		#endif
		
		EscolhaFuncionario();
    }

    while(fgets(ler, 100, file) != NULL){ 
        printf("%s", ler);
    }
    
    fclose(file);
     
    
	#ifdef OS_Windows
		Sleep(1000);
	
	#else
		sleep(1);
	
	#endif
	
    printf("\n\nDeseja procurar por outro paciente?\n");
    scanf("%3[^\n]s");
    LimpaBuffer();
    
    if(!stricmp(gresposta, "Sim")){
    	    	
		#ifdef OS_Windows
			system("cls");
	
		#else
			system("clear");
	
		#endif
		
    	ArquivoPaciente();
	}
	
	#ifdef OS_Windows
		system("cls");
	
	#else
		system("clear");
	
	#endif
	
	EscolhaFuncionario();
}


/****
 * Descri��o: Verifica e conta os sintomas de acordo com cada "banco de dados".
 *
 * Par�metros: Entrada: SintomasPaciente[][30] - matriz de caractere que cont�m os sintomas do paciente informado no bloco de "CadastraSintoma()",
 *			   
 * Valor de retorno: Inteiro que representa o valor correspondente a cor da classifica��o atribu�da ao paciente.
 *
 ****/
int Triagem(const char SintomasPaciente[][30]){
	int  ContAzul = 0, ContVerde = 0, ContAmarelo = 0, ContVermelho = 0;
	char LerAzul[120], LerVerde[120], LerAmarelo[120], LerVermelho[120];
	int  i = 0;
	char *token;
	
	FILE *BancoAzul;
	
	BancoAzul = fopen("azul.txt", "r");
	
	if(BancoAzul == NULL){
		printf("N�o foi poss�vel acessar o banco de sintomas, por favor, entre em contato com o suporte.");
		
		#ifdef OS_Windows
			Sleep(1500);
	
		#else
			sleep(2);
	
		#endif
		
		EscolhaFuncionario();
	}
	
	while(fgets(LerAzul, 120, BancoAzul) != NULL);
	
	token = strtok(LerAzul, ",");
	
	if(token == NULL){
		printf("Arquivo corrompido!");
		
		#ifdef OS_Windows
			Sleep(1000);
	
		#else
			sleep(1);
	
		#endif
		
		EscolhaFuncionario();
	}
	
		
	while(i < 4){
		if(!stricmp(token, SintomasPaciente[i])){
			ContAzul++;
		}
		
		i++;
		
		if(i == 4){
			i = 0;
			break;
		}
	}
	
	while(token != NULL){
		token = strtok(NULL, ",");
		
		while(i < 4){
			
			if(!stricmp(token, SintomasPaciente[i])){
				ContAzul++;
			}
			
			i++;
		}
		
		if(i == 4){
			i = 0;
		}

	}
	
	fclose(BancoAzul);
	

	FILE *BancoVerde;
	
	BancoVerde = fopen("verde.txt", "r");
	
	if(BancoVerde == NULL){
		printf("N�o foi poss�vel acessar o banco de sintomas, por favor, entre em contato com o suporte.");
		
		#ifdef OS_Windows
			Sleep(1500);
	
		#else
			sleep(2);
	
		#endif
		
		EscolhaFuncionario();
	}
	
	while(fgets(LerVerde, 120, BancoVerde) != NULL);
	
	token = strtok(LerVerde, ",");
	
	if(token == NULL){
		printf("Arquivo corrompido!");
		
		#ifdef OS_Windows
			Sleep(1500);
	
		#else
			sleep(2);
	
		#endif
		
		EscolhaFuncionario();
	}
	
		
	while(i < 4){
		if(!stricmp(token, SintomasPaciente[i])){
			ContVerde++;
		}
		
		i++;
		
		if(i == 4){
			i = 0;
			break;
		}
	}
	
	while(token != NULL){
		token = strtok(NULL, ",");
		
		while(i < 4){
			
			if(!stricmp(token, SintomasPaciente[i])){
				ContVerde++;
			}
			
			i++;
		}
		
		if(i == 4){
			i = 0;
		}

	}
	
	fclose(BancoVerde);
	

	FILE *BancoAmarelo;
	
	BancoAmarelo = fopen("amarelo.txt", "r");
	
	if(BancoAmarelo == NULL){
		printf("N�o foi poss�vel acessar o banco de sintomas, por favor, entre em contato com o suporte.");
		
		#ifdef OS_Windows
			Sleep(1500);
	
		#else
			sleep(2);
	
		#endif
		
		EscolhaFuncionario();
	}
	
	while(fgets(LerAmarelo, 120, BancoAmarelo) != NULL);
	
	token = strtok(LerAmarelo, ",");
	
	if(token == NULL){
		printf("Arquivo corrompido!");
		
		#ifdef OS_Windows
			Sleep(1500);
	
		#else
			sleep(2);
	
		#endif
		
		EscolhaFuncionario();
	}
	
		
	while(i < 4){
		if(!stricmp(token, SintomasPaciente[i])){
			ContAmarelo++;
		}
		
		i++;
		
		if(i == 4){
			i = 0;
			break;
		}
	}
	
	while(token != NULL){
		token = strtok(NULL, ",");
		
		while(i < 4){
			
			if(!stricmp(token, SintomasPaciente[i])){
				ContAmarelo++;
			}
			
			i++;
		}
		
		if(i == 4){
			i = 0;
		}

	}
	
	fclose(BancoAmarelo);
	

	FILE *BancoVermelho;
	
	BancoVermelho = fopen("vermelho.txt", "r");
	
	if(BancoVermelho == NULL){
		printf("N�o foi poss�vel acessar o banco de sintomas, por favor, entre em contato com o suporte.");
		
		#ifdef OS_Windows
			Sleep(1500);
	
		#else
			sleep(2);
	
		#endif
		
		EscolhaFuncionario();
	}
	
	while(fgets(LerVermelho, 120, BancoVermelho) != NULL);
	
	token = strtok(LerVermelho, ",");
	
	if(token == NULL){
		printf("Arquivo corrompido!");
		
		#ifdef OS_Windows
			Sleep(1500);
	
		#else
			sleep(2);
	
		#endif
		
		EscolhaFuncionario();
	}
	
		
	while(i < 4){
		if(!stricmp(token, SintomasPaciente[i])){
			ContVermelho++;
		}
		
		i++;
		
		if(i == 4){
			i = 0;
			break;
		}
	}
	
	while(token != NULL){
		token = strtok(NULL, ",");
		
		while(i < 4){
			
			if(!stricmp(token, SintomasPaciente[i])){
				ContVermelho++;
			}
			
			i++;
		}
		
		if(i == 4){
			i = 0;
		}

	}
	
	fclose(BancoVermelho);
	
	return CalculaClassificacao(ContAzul, ContVerde, ContAmarelo, ContVermelho);
}


/****
 * Descri��o: Utiliza a contagem correspondente a cada "banco de dados" para classificar o paciente em uma determinada cor.
 *
 * Par�metros: Entrada: ContAzul - contagem de sintomas referente ao "Banco Azul",
 *						ContVerde - contagem de sintomas referente ao "Banco Verde",
 *						ContAmarelo - contagem de sintomas referente ao "Banco Amarelo",
 *						ContVermelho - contagem de sintomas referente ao "Banco Vermelho".
 *
 * Valor de retorno: Inteiro que � associado a uma cor da classifica�ao, sendo: 1 - Azul, 2 - Verde, 3 - Amarelo e 4 - Vermelho.
 *
 ****/
int CalculaClassificacao(int ContAzul, int ContVerde, int ContAmarelo, int ContVermelho){
	int MaiorAzulVerde = 0, MaiorAmareloVermelho = 0, MaiorResultadoFinal = 0;
	int ArmazenaPrimeiroMaior = 0, ArmazenaSegundoMaior = 0;
	
	if(VerificacaoEspecial(ContAzul, ContVerde, ContAmarelo, ContVermelho) != 0){
		
		return VerificacaoEspecial(ContAzul, ContVerde, ContAmarelo, ContVermelho);
	}
	
	else{

		MaiorAzulVerde = (ContAzul + ContVerde + abs(ContAzul - ContVerde))/2;
	
		MaiorAmareloVermelho = (ContAmarelo + ContVermelho + abs(ContAmarelo - ContVermelho))/2;
	
		MaiorResultadoFinal = (MaiorAzulVerde + MaiorAmareloVermelho + abs(MaiorAzulVerde - MaiorAmareloVermelho))/2;
	
	
		if(MaiorResultadoFinal == ContAzul){
			return 1;
		}
	
		else if(MaiorResultadoFinal == ContVerde){
			return 2;
		}
	
		else if(MaiorResultadoFinal == ContAmarelo){
			return 3;
		}
	
		else if(MaiorResultadoFinal == ContVermelho){
			return 4;
		}
	}
}


/****
 * Descri��o: Realiza o cadastro dos sintomas do paciente, mas antes verifica se o mesmo j� foi cadastrado.
 *
 * Par�metros: Nenhum.
 *
 * Valor de retorno: Nenhum.
 *
 ****/
void CadastraSintomas(){
	char NomePacienteProcura[50], extensao [5] = ".doc";
	char NomePacienteCadastra[50], ExtSintomas[] = "_sintomas.txt";
	char NomePaciente[50];
	char SintomasPaciente[4][30];
	int  i = 1;
	
	printf("Insira o nome do paciente que deseja cadastrar os sintomas:\n");
	scanf("%49[^\n]s", NomePacienteProcura);
	LimpaBuffer();
	
	strcpy(NomePacienteCadastra, NomePacienteProcura);
	strcpy(NomePaciente, NomePacienteProcura);

	#ifdef OS_Windows
		Sleep(800);
		system("cls");
	
	#else
		sleep(1);
		system("clear");

	#endif
	
	strcat(NomePacienteProcura, extensao);
	
	FILE *sintomas;
	
	sintomas = fopen(NomePacienteProcura, "r");
	
	if(sintomas == NULL){
		printf("O paciente digitado n�o est� cadastrado no sistema, por favor, realize o cadastro e depois cadastre os sintomas.");

		#ifdef OS_Windows
			Sleep(1500);
			system("cls");
	
		#else
			sleep(2);
			system("clear");
	
		#endif
		
		EscolhaFuncionario();
	}
	
	else {
		
		fclose(sintomas);
		
		strcat(NomePacienteCadastra, ExtSintomas);
		
		sintomas = fopen (NomePacienteCadastra, "w");
		
		if(sintomas == NULL){
			printf("N�o foi poss�vel acessar o banco de dados para o cadastro dos sintomas do paciente, por favor, entre em contato com o suporte.");

			#ifdef OS_Windows
				Sleep(1500);
				system("cls");
	
			#else
				sleep(2);
				system("clear");
	
			#endif
			
			EscolhaFuncionario();	
		}
		
		printf("Insira um sintoma:\n");
		scanf("%29[^\n]s", SintomasPaciente[0]);
		LimpaBuffer();
		
		fprintf(sintomas, "\t\tSINTOMAS DO PACIENTE\n");
		fprintf(sintomas, "NOME:%s\n", NomePaciente);
		fprintf(sintomas, "\nSINTOMAS:%s\n", SintomasPaciente[0]);
		
		#ifdef OS_Windows
			system("cls");
	
		#else
			system("clear");
	
		#endif
		
		printf("Deseja inserir outro sintoma?\n");
		scanf("%3[^\n]s", gresposta);
		LimpaBuffer();

		#ifdef OS_Windows
			system("cls");
	
		#else
			system("clear");
	
		#endif
		
		if(!stricmp(gresposta, "Sim")){
			
			while(!stricmp(gresposta, "Sim") && i < 4){
				
				printf("Insira outro sintoma:\n");
				scanf("%29[^\n]s", SintomasPaciente[i]);
				LimpaBuffer();
				
				fprintf(sintomas, "\t %s\n", SintomasPaciente[i]);

				#ifdef OS_Windows
				system("cls");
	
				#else
				system("clear");
	
				#endif

				i++;
				
				if(i == 4){
					break;
				}
				
				printf("Deseja inserir outro sintoma?\n");
				scanf("%3[^\n]s", gresposta);
				LimpaBuffer();
				
				#ifdef OS_Windows
				system("cls");
	
				#else
				system("clear");
	
				#endif
			
			}
			
			fclose(sintomas);
		}
		
		printf("%d", Triagem(SintomasPaciente));
		
		EscolhaFuncionario();
	}
}

/****
 * Descri��o: Realiza uma compara��o espec�fica entre os contadores dos bancos, verificando quando dois espec�ficos s�o iguais, privilegiando o de maior prioridade.
 *
 * Par�metros: Entrada: ContAzul - contador de sintomas referente ao banco azul,
 *						ContVerde - contador de sintomas referente ao banco verde,
 * 						ContAmarelo - contador de sintomas referente ao bacno amarelo,
 *						ContVermelho - contador de sintomas referente ao banco vermelho.
 *
 * Valor de sa�da: Inteiro que representa a cor da classifica��o do paciente; nesses casos espec�ficos, priorizando a cor de maior prioridade.
 *
 ****/
int VerificacaoEspecial(int ContAzul, int ContVerde, int ContAmarelo, int ContVermelho){
	
	if((ContAzul == ContVerde) && (ContAzul != 0)){
		return 2;
	}
	
	else if((ContAzul == ContAmarelo) && (ContAzul != 0)){
		return 3;
	}
	
	else if((ContAzul == ContVermelho) && (ContAzul != 0)){
		return 4;
	}

	else if((ContVerde == ContAmarelo) && (ContVerde != 0)){
		return 3;
	}
	
	else if((ContVerde == ContVermelho) && (ContVerde != 0)){
		return 4;
	}
	
	else if((ContAmarelo == ContVermelho) && (ContAmarelo != 0)){
		return 4;
	}
	
	else{
		return 0;
	}
}


void LimpaBuffer(){
	char c;
	
	while(c = getchar() != '\n'){
	}
}
