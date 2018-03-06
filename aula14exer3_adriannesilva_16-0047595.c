// Adrianne Alves da Silva - 16/0047595
/*S�ntese 
	Objetivo: Armazenar e gerenciar dados sobre propriet�rios de autom�veis
	Entrada: nome, cpf, 
	Sa�da: sal�rios em ordem decrescente
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
		printf("Forne�a o valor do %d� sal�rio : ",(ordem+1));
		scanf("%f",&salario[ordem]);
		salario[ordem]=validaSalario(salario[ordem]);			
	}	
	troca(salario);
	printf("\n\nSal�rios em ordem decrescente: ");
	for(ordem=0;ordem<MAX;ordem++){
		printf("%.2f ",salario[ordem]);
	}
	
	return 0;
}

//SUBALGORITMO 
//	Objetivo : Ordenar sal�rios
//	Entrada : Endere�o inicial do vetor de sal�rios
//  Sa�da : Sem sa�da

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
//	Objetivo : Validar sal�rio
//	Entrada : sal�rio 
//  Sa�da : Sal�rio v�lido

float validaSalario(float salario){
	while(salario<880){
		printf("\n\nSal�rio Inv�lido, forne�a novamente : ");
		scanf("%f",&salario);
	}
	return salario;
}
