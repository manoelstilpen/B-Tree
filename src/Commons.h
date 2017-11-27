// Copyright (C) 2016 Manoel Stilpen

/* This file is part of B-Tree project.
 *
 * B-Tree project is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * B-Tree project is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 */

 /*
  * @Author: Manoel Stilpen
  * @Email: manoel@decom.ufop.br
  * @FullProject: https://github.com/manoelstilpen/B-Tree
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

enum Ordem {ASCENDING, DESCENDING, RANDOM};
enum Metodo {INDEXADO, BUSCA_BINARIA, ARVOREB, ARVOREB2};
enum Bool {false, true};

void printRegister(Registro* registro);
void printFile(char* nomeArquivo);
void printAnalysis(Analise* analise);

Analise* init_analysis();

#endif
