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
 * along with B-Tree.  If not, see <http://www.gnu.org/licenses/>.
 */

 /*
  * @Author: Manoel Stilpen
  * @Email: manoel@decom.ufop.br
  * @FullProject: https://github.com/manoelstilpen/B-Tree
  */

#include "Commons.h"

void printRegister(Registro* registro){
	printf("%d %ld %s\n", registro->key, registro->dado1, registro->dado2);
}

// used to check the binary file integrity
void printFile(char *nomeArquivo){
	Registro registro;
	FILE* arq = fopen(nomeArquivo, "rb");
    while (fread(&registro, sizeof(Registro), 1, arq) == 1) {
    	printRegister(&registro);
    }
    fclose(arq);
}

// initialize benchmark struct
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

// print benchmark data
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
