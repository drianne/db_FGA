// Aluna : Adrianne Alves da Silva - 16/0047595


/*
	SÍNTESE 

           Objetivo:   Gerenciar registros dos proprietários de veículos no Brasil  

           Entrada:   nome, rg, telefone , endereco e registro do proprietário, placa, modelo e renavam dos veículos  

           Saída:  nome, rg, telefone , endereco e registro do proprietário, placa, modelo e renavam dos veículos 
*/

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define MNOME 40
#define MRUA 30
#define MBAIRRO 30
#define MESTADO 30
#define MCIDADE 30
#define MMODELO 30
#define MPLACA 10

typedef struct endereco
{
	char rua [MRUA];
	char bairro [MBAIRRO];
	char cidade [MCIDADE];
	char estado [MESTADO];
} endereco;

typedef struct proprietario{
	char nome [MNOME];
	int rg;
	int telefone;
	int cnh;
	endereco localizacao;
} proprietario;

typedef struct veiculo{
	int rgProprietario; // Chave de identificação do proprietário
	char modelo [MMODELO];
	int ano;
	char placa [MPLACA];
	int renavan;
}veiculo;

void apresentarmenu();
void cadastrarProprietario();
int validarg(int rg);
void validaNome(char *nome);
void cadastrarCarro();
void listarCarros();
void listarProprietarios();

int main(){
	
	int opcao;
do{
	apresentarmenu();
	scanf("%d",&opcao);
    __fpurge(stdin);
	switch(opcao){
		case 1:
            cadastrarProprietario();
		break;
		case 2: 
			cadastrarCarro();
		break;
		case 3: 
			listarProprietarios();
		break;
		case 4: 
			listarCarros();
		break;
		case 0:
			printf("\nO programa esta sendo encerrado ...\n\n");
		break;
		default:
			printf("\nOpcao invalida!\n\n");
	}
}while(opcao != 0);

	return 0;
}

void apresentarmenu(){
	puts("\n\n ###### GERENCIA DE PROPRIETARIOS DE VEICULOS NO BRASIL ######");
	puts(" 1 - CADASTRAR PROPRIETÁRIO");
	puts(" 2 - CADASTRAR VEÍCULO");
	puts(" 3 - LISTAR PROPRIETARIOS");
	puts(" 4 - LISTAR VEÍCULOS");
	puts(" 0 - SAIR");
	puts(" --> ");
}

void cadastrarProprietario(){

//Declarações de variáveis

    FILE *arquivo = NULL;
    proprietario dono;

//Instruções

    if((arquivo=fopen("proprietariosbrasil.bin","ab"))==NULL){
        arquivo=fopen("proprietariosbrasil.bin","wb");
    }
    if(arquivo == NULL){
        puts("\nErro ! Nao foi possivel abrir esse arquivo!\n");
        getchar();	        
        __fpurge(stdin); 
    }else{
    puts("\n-------- DADOS DO PROPRIETARIO -------\n");
	printf("Nome: ");
	fgets(dono.nome, MNOME, stdin);
    __fpurge(stdin);
    do{
		printf("\nRg do Proprietario: ");
        	scanf("%d", &dono.rg);
	}while(!validarg(dono.rg));
	__fpurge(stdin);
	printf("\nTelefone: ");
	scanf("%d", &dono.telefone);
	printf("\nCNH: ");
	scanf("%d",&dono.cnh);
	__fpurge(stdin);
    printf("\nEndereco -----------------------------\n");
    printf("\nRua:");
    fgets(dono.localizacao.rua,MRUA, stdin);
    __fpurge(stdin);
    printf("\nBairro:");
	fgets(dono.localizacao.bairro,MBAIRRO,stdin);
    __fpurge(stdin);
	printf("\nCidade:");
    fgets(dono.localizacao.cidade,MCIDADE, stdin);
    __fpurge(stdin);
	printf("\nEstado:");
	fgets(dono.localizacao.estado,MESTADO,stdin);
    __fpurge(stdin);	
	fwrite(&dono, sizeof(proprietario), 1, arquivo);
	fclose(arquivo);
    }
}

void cadastrarCarro(){

//Declarações de variáveis

    FILE *arquivo = NULL;
    veiculo carro;

//Instruções

typedef struct veiculo{
	int rgProprietario; // Chave de identificação do proprietário
	char modelo [MMODELO];
	int ano;
	char placa[MPLACA];
	int renavan;
}veiculo;

    if((arquivo=fopen("carrosbrasil.bin","ab"))==NULL){
        arquivo=fopen("carrosbrasil.bin","wb");
    }
    if(arquivo == NULL){
        puts("\nErro ! Nao foi possivel abrir esse arquivo!\n");
        getchar();	
        __fpurge(stdin);        
    }else{
    puts("\n-------- DADOS DO VEÍCULO -------\n");	
	do{
		printf("\nRG do proprietário: ");
		scanf("%d",&carro.rgProprietario);
	}while(!validarg(carro.rgProprietario));	
    __fpurge(stdin);
    fflush(stdin);
	printf("\nModelo: ");
	fgets(carro.modelo, MMODELO, stdin);
	__fpurge(stdin);
	printf("\nAno: ");
	scanf("%d",&carro.ano);
	__fpurge(stdin);
	printf("\nPlaca: ");
	fgets(carro.placa, MPLACA, stdin);
	__fpurge(stdin);
	printf("\nRenavam: ");
	scanf("%d",&carro.renavan);
    __fpurge(stdin);	
	fwrite(&carro, sizeof(veiculo), 1, arquivo);
	fclose(arquivo);
    }
}

void validaNome(char *nome){
    while(strlen(nome) < 5 || strstr(nome, " ") == NULL){
        printf("Inválido!\n Nome: ");
        fgets(nome, MNOME, stdin);        
        fflush(stdin);
	__fpurge(stdin);
    }
    //Acrescentar \0
    if(nome[strlen(nome)-1] == '\n')
        nome[strlen(nome)-1] = '\0';
}

int validarg(int rg){
	if(rg<1000) // Teste genérico
		return 0;
	return 1;
}

void listarProprietarios(){
//Declaração das variáveis
    proprietario dono;
    FILE *arquivo = 0;

//Instruções
	if((arquivo=fopen("proprietariosbrasil.bin","rb"))==NULL){
        printf("\n\nNao ha registro de proprietarios de carros!");
    }else{
    	fseek(arquivo, 0, SEEK_SET); //Aponta pro início do arquivo
    	printf("\n ---------- Lista de Proprietarios ---------- \n");
	    while(fread(&dono, sizeof(proprietario),1,arquivo)==1) { 	
	    	printf("\n ---------- Dados do Proprietario ---------- \n");
        	printf("\n Nome : %s\n", dono.nome);
        	printf("\n Rg : %d\n", dono.rg);
        	printf("\n Telefone : %d\n", dono.telefone);
        	printf("\n CNH: %d", dono.cnh);
        	printf("\n\nEndereco---------------------------------- :\n\n");
        	printf("\n Rua : %s", dono.localizacao.rua );
        	printf("\n Bairro : %s", dono.localizacao.bairro );
        	printf("\n Cidade : %s", dono.localizacao.cidade );
        	printf("\n Estado : %s\n", dono.localizacao.estado );
        }
	    fclose(arquivo);
	}

}

void listarCarros(){
//Declaração das variáveis
    veiculo carro;
    FILE *arquivo = 0;
    
//Instruções
	if((arquivo=fopen("carrosbrasil.bin","rb"))==NULL){
        printf("\n\nNao ha registro de proprietarios de carros!");
    }else{
    	fseek(arquivo, 0, SEEK_SET); //Aponta pro início do arquivo
    	printf("\n ---------- Lista de Veiculos Cadastrados ---------- \n");
	    while(fread(&carro, sizeof(veiculo),1,arquivo)==1) { 	
	    	printf("\n ---------- Dados do Veiculo ---------- \n");
        	printf("\n RG do proprietario : %d\n", carro.rgProprietario);
        	printf("\n Modelo : %s\n", carro.modelo);
        	printf("\n Ano : %d\n", carro.ano);
        	printf("\n Placa: %s", carro.placa);
        	printf("\n Renavam: %d\n", carro.renavan);
        }
	    fclose(arquivo);
	}

}