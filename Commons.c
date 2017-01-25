#include "Commons.h"

void printRegister(Registro* registro){
	printf("%d %ld %s\n", registro->key, registro->dado1, registro->dado2);
}

//usado apenas para conferir integridade do arquivo binario
void printFile(char *nomeArquivo){
	Registro registro;
	FILE* arq = fopen(nomeArquivo, "rb");
    while (fread(&registro, sizeof(Registro), 1, arq) == 1) {
    	printRegister(&registro);
    }
    fclose(arq);
}

Analise* init_analysis(){
	Analise* analise = (Analise*) malloc(sizeof(Analise));
	analise->transferencias_preparacao = 0;
	analise->transferencias_pesquisa = 0;
	analise->comparacoes_preparacao = 0;
	analise->comparacoes_pesquisa = 0;
	analise->tempo_preparacao = 0;
	analise->tempo_pesquisa = 0;
	analise->tempo_total = 0;

	return analise;
}

void printAnalysis(Analise* analise){
	#ifdef PRINT
		printf("\nPREPROCESSING:\n");
		printf("TRANSFERS: %d COMPARATIONS: %d TIME: %f\n", 
			analise->transferencias_preparacao, analise->comparacoes_preparacao, analise->tempo_preparacao);
		printf("SEARCH:\n");
		printf("TRANSFERS: %d COMPARATIONS: %d TIME: %f\n", 
			analise->transferencias_pesquisa, analise->comparacoes_pesquisa, analise->tempo_pesquisa);
		printf("=================================================================\n");
	#endif

	#ifndef PRINT
		printf("%d|%f|%d\n", analise->comparacoes_preparacao, analise->tempo_preparacao, analise->transferencias_preparacao);
		printf("%d|%f|%d\n", analise->comparacoes_pesquisa, analise->tempo_pesquisa, analise->transferencias_pesquisa);		
	#endif
}