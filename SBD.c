// Aluna : Adrianne Alves da Silva - 16/0047595


/*
	SÍNTESE 

           Objetivo:   Gerenciar registros dos proprietários de veículos no Brasil  

           Entrada:   nome, cpf, telefone , endereco e registro do proprietário, placa, chassi e renavam dos veículos  

           Saída:  nome, cpf, telefone , endereco e registro do proprietário, placa, chassi e renavam dos veículos 
*/

//Bibliotecas

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NUMEROVEICULOS 100 //Número máximo de veículos
#define RUA 50 
#define BAIRRO 50 
#define CIDADE 50 
#define ESTADO 30 
#define PLACA 9
#define NOME 40

// Declaração de estruturas ou registros


typedef struct endereco{
	char rua [RUA];
	char bairro [BAIRRO];
	char cidade [CIDADE];
	char estado [ESTADO];
} endereco;

typedef struct automovel{
	char placa [PLACA];
	int chassi;
	int renavam;
} automovel;

typedef struct proprietario{
	char nome [NOME];
	int cpf;
	int telefone;
	endereco localizacao;
	int registro;	
	automovel veiculos [NUMEROVEICULOS];
} proprietario;

// Declaração de funções

void menu();
void cadastroProprietario();
void validaNome(char *nome);
int validacpf(int cpf);
int validaTelefone(int tel);

int main(){

//Declaração de variáveis
	char opcaomenu;

	do{
		menu();
		opcaomenu = getchar();
		__fpurge(stdin);

		switch (toupper(opcaomenu)){
		 	case 'C':
			      	cadastroProprietario();
			      	system("CLS"); 
			      	break; 
		 	case 'L':
		//	      	listaCadastros();
			      	system("CLS");
			      	break;
		 	case 'S':
				system("CLS");
				printf("... Programa sendo finalizado");
				break;
		 	default:
		        puts("Essa opcao nao esta disponivel!");
	      	}
	}while(toupper(op)!='S');
	return 0;
}

//------------- FUNÇÕES ---------------

//Objetivo: Apresentar o menu de opções
//Parametros: sem parametros
//Retorno: sem retorno

void menu(){
	printf("-------- CADASTRO DE PROPRIETÁRIOS DE VEÍCULOS  --------\n");
	printf("1 - CADASTRAR PROPRIETÁRIO \n");
	printf("2 - LISTAR CADASTROS\n");
	printf("0 - SAIR\n\n");
	printf("--->");		
}

//Objetivo: Cadastrar Proprietário e Seus Veículos
//Parametros: sem parametros
//Retorno: sem retorno

void cadastro(){

//Declarações de variáveis

    FILE *arquivo = 0;
    proprietario dono;
    automovel carro;
    char continuar = 'S', 
    int numerodecarros, cadastrocarros;

//Instruções
    if((arquivo=fopen("proprietariosbrasil.bin","ab"))==NULL){
        arquivo=fopen("proprietariosbrasil.bin","wb");
    }
    if(arquivo == NULL){
        puts("Nao foi possivel abrir esse arquivo");
        getchar();
	fflush(stdin);
    }else{
    puts("\n-------- DADOS DO PROPRIETARIO -------\n");
	printf("Nome: ");
	fgets(dono.nome, NOME, stdin);
    __fpurge(stdin);

    //Tratar particularidade do fgets
	if(dono.nome[strlen(dono.nome)-1] == '\n')
            dono.nome[strlen(dono.nome)-1] = '\0';
	validaNome(dono.nome);
    printf("\nEndereco -----------------------------\n");
    printf("\nRua:");
    fgets(dono.localizacao.rua, RUA, stdin);
    // O uso de dois diferentes comando de limpar buffer diz respeito à erros no SO Windows e linux mint
	fflush(stdin);
       __fpurge(stdin);
    printf("\nBairro:");
	fgets(dono.localizacao.bairro,BAIRRO,stdin);
    fflush(stdin);
       __fpurge(stdin);
	printf("\nCidade:");
    fgets(dono.localizacao.cidade,CIDADE, stdin);
    fflush(stdin);
      __fpurge(stdin);
	printf("\nEstado:");
	fgets(dono.localizacao.estado,ESTADO,stdin);
	fflush(stdin);
      __fpurge(stdin);
	do{
		printf("CPF do Proprietario: ");
        	scanf("%d", &dono.cpf);
	}while(!validacpf(dono.cpf));

	do{
                printf("Telefone: ");
		scanf("%d", &dono.telefone);
	}while(!validaTel(dono.telefone));

	printf("Numero de Carros: ");
	scanf("%d", &numerodecarros);
	fflush(stdin);
        __fpurge(stdin);

	fwrite(&dono, sizeof(proprietario), 1, arquivo);

	for(cadastrocarros=1; cadastrocarros<=numerodecarros; cadastrocarros++){
		printf("Placa do automovel %d : ", cadastrocarros);
	        fgets(carro.placa, PLACA, stdin);
            fflush(stdin);
                __fpurge(stdin);
	        printf("Chassi %d: ", cadastrocarros);
        	fgets(carro.chassi, sizeof(int), stdin);
		    fflush(stdin);
	            __fpurge(stdin);
        	printf("Renavam do automovel %d: ",cadastrocarros);
		    scanf("%d", &carro.renavan);
		 fwrite(&carro, sizeof(automovel), 1, arquivo);
	}
	fflush(stdin);
        __fpurge(stdin);

	fclose(arquivo);
    }
}


//Objetivo: Validar nomes 
//Parametros: nome
//Retorno: sem retorno

void validaNome(char *nome){
    while(strlen(nome) < 5 || strstr(nome, " ") == NULL){
        printf("Inválido!\n Nome: ");
        fgets(nome, NOME, stdin);
        //Tratar particularidade do fgets
        if(nome[strlen(nome)-1] == '\n')
            nome[strlen(nome)-1] = '\0';
        fflush(stdin);
	__fpurge(stdin);

    }
}

//Objetivo: validar CPF do proprietário
//Parametros: Número do CPF
//Retorno: 1 se válido e 0 se inválido 

int validacpf(int cpf){
	if(cpf<100000) // Teste genérico
		return 0;
	return 1;
}

//Objetivo: validar o número de telefone 
//Parametros: número de telefone
//Retorno: 1 se válido  e 0 se inválido 

int validaTelefone(int telefone){
        if(telefone<10000000) // Teste genérico
                return 0;
        return 1;
}

