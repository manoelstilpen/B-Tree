/*
 * Author: Manoel Stilpen
 * Email: manoelvstilpen@gmail.com
 */
 
#ifndef TP1_COMMONS_H_
#define TP1_COMMONS_H_

#define TAM_CHAR_REGISTRO 5
#define PRINT

#include "stdio.h"
#include <stdlib.h>

typedef struct{
	int key;
	long dado1;
	char dado2[TAM_CHAR_REGISTRO];
} Registro;

typedef struct {
	int transferencias_pesquisa;
	int transferencias_preparacao;
	int comparacoes_pesquisa;
	int comparacoes_preparacao;
	float tempo_pesquisa;
	float tempo_preparacao;
	float tempo_total;
} Analise;

enum Ordem {CRESCENTE, DECRESCENTE, ALEATORIO};
enum Metodo {INDEXADO, BUSCA_BINARIA, ARVOREB, ARVOREB2};
enum Bool {false, true};

void printRegister(Registro* registro);
void printFile(char* nomeArquivo);
void printAnalysis(Analise* analise);

Analise* init_analysis();

#endif