// Adrianne Alves da Silva - 16/0047595
/*Síntese 
	Objetivo: Armazenar e gerenciar dados sobre proprietários de automóveis
	Entrada: nome, cpf, 
	Saída: salários em ordem decrescente
*/

#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#define MAX 3

int main(){
	
	setlocale(LC_ALL,"Portuguese");
	
	float salario[MAX],*atual;
	int ordem;
	void troca(float *salario);
	float validaSalario(float salario);
	
	for(ordem=0;ordem<MAX;ordem++){
		printf("Forneça o valor do %dº salário : ",(ordem+1));
		scanf("%f",&salario[ordem]);
		salario[ordem]=validaSalario(salario[ordem]);			
	}	
	troca(salario);
	printf("\n\nSalários em ordem decrescente: ");
	for(ordem=0;ordem<MAX;ordem++){
		printf("%.2f ",salario[ordem]);
	}
	
	return 0;
}

//SUBALGORITMO 
//	Objetivo : Ordenar salários
//	Entrada : Endereço inicial do vetor de salários
//  Saída : Sem saída

void troca(float *salario){
	
	float auxiliar, compara;
	int posicao,proximo;
	
	for (posicao=0;posicao<MAX; posicao++) {
		for(proximo=posicao+1;proximo<MAX;proximo++){ 
			if (salario[proximo]>salario[posicao]){ 
				auxiliar=salario[posicao]; 
				salario[posicao]=salario[proximo]; 
				salario[proximo]=auxiliar;
			}
		} 
	}
}

//SUBALGORITMO 
//	Objetivo : Validar salário
//	Entrada : salário 
//  Saída : Salário válido

float validaSalario(float salario){
	while(salario<880){
		printf("\n\nSalário Inválido, forneça novamente : ");
		scanf("%f",&salario);
	}
	return salario;
}
