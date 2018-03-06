// Aluna : Adrianne Alves da Silva - 16/0047595


/*
	SÍNTESE 

           Objetivo:   Gerenciar registros dos proprietários de veículos no Brasil  

           Entrada:   nome, rg, telefone , endereco e registro do proprietário, placa, modelo e renavam dos veículos  

           Saída:  nome, rg, telefone , endereco e registro do proprietário, placa, modelo e renavam dos veículos 
*/

//Bibliotecas

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Definindo constantes de tamanho máximo

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
	int chassi;
	char placa [PLACA];	
	int renavam;
} automovel;

typedef struct proprietario{
	char nome [NOME];
	int rg;
	int telefone;
	endereco localizacao;
	int registro;	
	int quantidadecarros;
	automovel veiculos [NUMEROVEICULOS];
} proprietario;

// Declaração de funções

void menu();
void cadastroProprietario();
void validaNome(char *nome);
int validarg(int rg);
void listaProprietarios();

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
			      	break; 
		 	case 'L':
			      	listaProprietarios();
			      	break;
		 	case 'S':
				printf("\n... Programa sendo finalizado\n");
				break;
		 	default:
		        printf("\nEssa opcao nao esta disponivel!");
	      	}
	}while(toupper(opcaomenu)!='S');
	return 0;
}

//------------- FUNÇÕES ---------------


//Objetivo: Apresentar o menu de opções
//Parametros: sem parametros
//Retorno: sem retorno

void menu(){
	printf("\n\n-------- CADASTRO DE PROPRIETÁRIOS DE VEÍCULOS  --------\n\n");
	printf("C - CADASTRAR PROPRIETÁRIO \n");
	printf("L - LISTAR CADASTROS\n");
	printf("S - SAIR\n\n");
	printf("--->");		
}

// ----------- VALIDAÇÃO --------------

//Objetivo: Validar nomes 
//Parametros: nome
//Retorno: sem retorno

void validaNome(char *nome){
    while(strlen(nome) < 5 || strstr(nome, " ") == NULL){
        printf("Inválido!\n Nome: ");
        fgets(nome, NOME, stdin);
        //Acrescentar \0
        if(nome[strlen(nome)-1] == '\n')
            nome[strlen(nome)-1] = '\0';
        fflush(stdin);
	__fpurge(stdin);

    }
}


//Objetivo: validar rg do proprietário
//Parametros: Número do rg
//Retorno: 1 se válido e 0 se inválido 

int validarg(int rg){
	if(rg<1000) // Teste genérico
		return 0;
	return 1;
}

// ----------- PRINCIPAIS --------------

//Objetivo: Cadastrar Proprietário e Seus Veículos
//Parametros: sem parametros
//Retorno: sem retorno

void cadastroProprietario(){

//Declarações de variáveis

    FILE *arquivo = 0;
    proprietario dono;
    automovel carro;
    char continuar = 'S'; 
    int cadastrocarros;

//Instruções
    if((arquivo=fopen("proprietariosbrasil.bin","ab"))==NULL){
        arquivo=fopen("proprietariosbrasil.bin","wb");
    }
    if(arquivo == NULL){
        puts("\n Nao foi possivel abrir esse arquivo\n");
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
		printf("\nRg do Proprietario: ");
        	scanf("%d", &dono.rg);
	}while(!validarg(dono.rg));
	fflush(stdin);
      __fpurge(stdin);
    printf("\nTelefone: ");
	scanf("%d", &dono.telefone);
	fflush(stdin);
      __fpurge(stdin);
	printf("\nNumero de Carros: ");
	scanf("%d", &dono.quantidadecarros);
	fflush(stdin);
        __fpurge(stdin);

	fwrite(&dono, sizeof(proprietario), 1, arquivo);

	for(cadastrocarros=1; cadastrocarros<=dono.quantidadecarros; cadastrocarros++){
		printf("\nPlaca do automovel %d : ", cadastrocarros);
		fflush(stdin);
                __fpurge(stdin);
		fgets(carro.placa, PLACA, stdin);
        fflush(stdin);
            __fpurge(stdin);
	    printf("\nChassi %d: ", cadastrocarros);
	    scanf("%d", &carro.chassi);
		fflush(stdin);
	         __fpurge(stdin);
        printf("\nRenavam do automovel %d: ",cadastrocarros);
		scanf("%d",&carro.renavam);
		fwrite(&carro, sizeof(automovel), 1, arquivo); 
	}
	fflush(stdin);
        __fpurge(stdin);

	fclose(arquivo);
    }
}

//Objetivo: listar todos os cadastros 
//Parametros: sem parametros
//Retorno: sem retorno

void listaProprietarios(){

//Declaração das variáveis
    int numerodecadastros=0, percorre, quantidade,i;
    proprietario dono;
    FILE *arquivo = 0;
    char condicao;
//Instruções
	if((arquivo=fopen("proprietariosbrasil.bin","rb"))==NULL){
        printf("Nao ha registro de proprietarios de carros");
    }else{
    	fseek(arquivo, 0, SEEK_SET);
    	printf("\n ---------- Lista de Proprietarios ---------- \n");
	    while(fread(&dono, sizeof(proprietario),1,arquivo)==1) { 	
	    	printf("\n ---------- Dados do Proprietario ---------- \n");
        	printf("\n Nome : %s\n", dono.nome);
        	printf("\n Rg : %d\n", dono.rg);
        	printf("\n Telefone : %d\n", dono.telefone);
        	printf("\n\n Endereco :\n\n");
        	printf("\n Rua : %s", dono.localizacao.rua );
        	printf("\n Bairro : %s", dono.localizacao.bairro );
        	printf("\n Cidade : %s", dono.localizacao.cidade );
        	printf("\n Estado : %s", dono.localizacao.estado );
        	printf("\n\n ---------- Veiculos deste Proprietário ----------\n ");
        	for(i =0; i<dono.quantidadecarros; i++){
        		if(fread(&dono.veiculos[i],sizeof(automovel),1,arquivo)!=1){
					printf("\n\n --- Erro na leitura --\n\n ");
					system("Pause");
				}
				else{
					printf("\n\n->Carro %d \n\n", (i+1));
        			printf(" Placa : %s", dono.veiculos[i].placa);
        			printf(" Chassi: %d", dono.veiculos[i].chassi);
        			printf("\n Renavam  : %d", dono.veiculos[i].renavam);	
				}        		
        	}
       	}
	    	fclose(arquivo);
	}
}





