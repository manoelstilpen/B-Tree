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

#include "B+Tree.h"

void search_in_tree(int key, Node** ap, Analise* analysis){
	int i=1;
	Node* pag = *ap;

	if((*ap)->type == INTERNAL){

		while(i < pag->pag.internal.quant && key > pag->pag.internal.keys[i-1]){
			i++;
			analysis->comparacoes_pesquisa++;
		}

		analysis->comparacoes_pesquisa++;
		if(key < pag->pag.internal.keys[i-1]){
			search_in_tree(key, &pag->pag.internal.pointers[i-1], analysis);
		} else {
			search_in_tree(key, &pag->pag.internal.pointers[i], analysis);
		}

		return;
	}

	while(i<pag->pag.external.quant && key > pag->pag.external.registers[i-1].key){
		i++;
		analysis->comparacoes_pesquisa++;
	}

	analysis->comparacoes_pesquisa++;
	if(key == pag->pag.external.registers[i-1].key){
		#ifdef PRINT
			printf("THE KEY %d WERE FOUND!!\n", key);
			printRegister(&pag->pag.external.registers[i-1]);
		#endif
	} else {
		printf("THE KEY %d WERE NOT FOUND!\n", key);
	}

	return;
}

void insertRegisterInArray(Registro* reg, Node** page, Analise* analysis){
	if((*page)->type == LEAF){
		int i=0;
		int quant = (*page)->pag.external.quant;

		if(quant >= ORDER_LEAF) printf("OVERFLOW REGISTERS!\n");

		while(i < quant && reg->key > (*page)->pag.external.registers[i].key){
			i++;
			analysis->comparacoes_preparacao++;
		}

		for(int j=quant ; j>i ; j--){
			(*page)->pag.external.registers[j] = (*page)->pag.external.registers[j-1];
		}

		(*page)->pag.external.registers[i] = *reg;
		(*page)->pag.external.quant++;
	} else {
		printf("ERROR: NODE IS NOT A LEAF NODE at insertRegisterInArray()\n");
	}
}

void insertKeyInArray(int key, Node** page, Analise* analysis){
	if((*page)->type == INTERNAL){
		int i=0;
		int quant = (*page)->pag.internal.quant;

		if(quant >= ORDER+2) printf("OVERFLOW KEYS!\n");

		while(i < quant && key > (*page)->pag.internal.keys[i]){
			i++;
			analysis->comparacoes_preparacao++;
		}

		for(int j=quant ; j>i ; j--){
			(*page)->pag.internal.keys[j] = (*page)->pag.internal.keys[j-1];
		}

		(*page)->pag.internal.keys[i] = key;
		(*page)->pag.internal.quant++;

	} else {
		printf("ERROR: NODE IS NOT A.... at insertKeyInArray()\n");
	}
}

void insertPointerInArray(Node* pointer, Node** page, Analise* analysis){
	if((*page)->type == INTERNAL){
		int i=0;
		int quant = (*page)->pag.internal.quant;

		if(quant >= ORDER+3) printf("OVERFLOW POINTERS!\n");

		if(pointer->type == LEAF){
			while(i < quant && pointer->pag.external.registers[0].key >= (*page)->pag.internal.keys[i]){
				i++;
				analysis->comparacoes_preparacao++;
			}
		} else {
			while(i < quant && pointer->pag.internal.keys[0] >= (*page)->pag.internal.keys[i]){
				i++;
				analysis->comparacoes_preparacao++;
			}
		}

		for(int j=quant ; j>i ; j--){
			(*page)->pag.internal.pointers[j] = (*page)->pag.internal.pointers[j-1];
		}

		(*page)->pag.internal.pointers[i] = pointer;

	} else{
		printf("ERROR: NODE IS NOT A.... at insertPointerInArray()\n");
	}
}

void insert_in_tree(Registro* reg, Node* page, int* overflow, Node** no_retorno, int* key_retorno, Analise* analysis){

	if((page)->type == LEAF){

		if((page)->pag.external.quant < ORDER_LEAF){
			//THERE'S FREE SPACE
			insertRegisterInArray(reg, &page, analysis);

		} else {
			// WHEN PAGE IS FULL - DIVIDE NODE

			(*no_retorno) = (Node*) malloc(sizeof(Node));
			(*no_retorno)->type = LEAF;
			(*no_retorno)->pag.external.quant = ORDER_LEAF/2;
			(page)->pag.external.quant = ORDER_LEAF/2;
			for(int i=ORDER_LEAF/2 ; i<ORDER_LEAF ; i++){
				(*no_retorno)->pag.external.registers[i-(ORDER_LEAF/2)] = (page)->pag.external.registers[i];
			}

			// DEFINES WHERE TO INSERT THE NEW REGISTER
			if(reg->key > (page)->pag.external.registers[(ORDER_LEAF/2)-1].key){
				//NEW REGISTER NEED TO BE INSERTED IN THE NEW NODE
				insertRegisterInArray(reg, no_retorno, analysis);
			} else {
				insertRegisterInArray(reg, &page, analysis);
			}

			*key_retorno = (*no_retorno)->pag.external.registers[0].key;
			*overflow = true;
		}
	} else {
		//CASE PAGE IS NOT LEAF NODE
		int i = 1;
		while(i < (page)->pag.internal.quant && reg->key > (page)->pag.internal.keys[i]) i++;

		int local_overflow = false;
		Node* novo;
		int new_key;

		analysis->comparacoes_preparacao++;
		if(reg->key < (page)->pag.internal.keys[i-1]){
			insert_in_tree(reg, (page)->pag.internal.pointers[i-1], &local_overflow, &novo, &new_key, analysis);
		} else {
			insert_in_tree(reg, (page)->pag.internal.pointers[i], &local_overflow, &novo, &new_key, analysis);
		}

		if(local_overflow == true){

			if((page)->pag.internal.quant < ORDER){
				insertKeyInArray(new_key, &page, analysis);
				insertPointerInArray(novo, &page, analysis);

			} else {

				// pegar a key que deve subir
				// inserir a key que chegou
				// dividir o no em dois

				insertKeyInArray(new_key, &page, analysis);
				*key_retorno = (page)->pag.internal.keys[ORDER/2];
				insertPointerInArray(novo, &page, analysis);

				(*no_retorno) = (Node*) malloc(sizeof(Node));
				(*no_retorno)->type = INTERNAL;
				(*no_retorno)->pag.internal.quant = ORDER/2;
				(page)->pag.internal.quant = ORDER/2;

				for(int i=0 ; i<ORDER/2 ; i++){
					(*no_retorno)->pag.internal.keys[i] = (page)->pag.internal.keys[i+(ORDER/2)+1];
				}

				for(int i=0 ; i<(ORDER/2)+1 ; i++){
					//printf("%p\n", (page)->pag.internal.pointers[i+(ORDER/2)+1]);
					(*no_retorno)->pag.internal.pointers[i] = (page)->pag.internal.pointers[i+(ORDER/2)+1];
				}


				*overflow = true;
			}
		}
	}
}

void insert_register(Registro* reg, Node** root, Analise* analysis){
	// tree initially empty
	if((*root) == NULL){
		*root = (Node*) malloc(sizeof(Node));
		(*root)->type = LEAF;
		(*root)->pag.external.quant = 1;
		(*root)->pag.external.registers[0] = *reg;
		return;
	}

	int overflow = false;
	Node* novo;
	int new_key;
	insert_in_tree(reg, *root, &overflow, &novo, &new_key, analysis);

	if(overflow == true){
		if((*root)->type == LEAF){
			Node* aux2 = (Node*) malloc(sizeof(Node));
			aux2->type = LEAF;
			aux2->pag.external.quant = (*root)->pag.external.quant;
			for(int i=0 ; i<(*root)->pag.external.quant ; i++){
				aux2->pag.external.registers[i] = (*root)->pag.external.registers[i];
			}

			Node* aux = (Node*) malloc(sizeof(Node));
			aux->type = INTERNAL;
			aux->pag.internal.quant = 1;
			aux->pag.internal.keys[0] = new_key;
			aux->pag.internal.pointers[0] = aux2;
			aux->pag.internal.pointers[1] = novo;

			*root = aux;
		} else {

			Node* new_head = (Node*) malloc(sizeof(Node));
			new_head->type = INTERNAL;
			new_head->pag.internal.quant = 1;
			new_head->pag.internal.keys[0] = new_key;
			new_head->pag.internal.pointers[0] = *root;
			new_head->pag.internal.pointers[1] = novo;

			*root = new_head;

		}
	}

}

Analise* run_bPlus_tree(char* file_name, int search_key){
	FILE* arq;
	if((arq = fopen(file_name, "rb")) == NULL) printf("FILE ERROR\n");

	Registro x;
	Node* root;

	Analise* analysis = init_analysis();

	// init generating tree
	clock_t begin = clock();
		#ifdef PRINT
			printf("GENERATING B* TREE...\n");
		#endif
		init_node(&root);
		while(fread(&x, sizeof(Registro), 1, arq) == 1){
			analysis->transferencias_preparacao++;
			insert_register(&x, &root, analysis);
		}

		fclose(arq);
	analysis->tempo_preparacao = (double) (clock() - begin)/CLOCKS_PER_SEC;

	#ifdef PRINT
		printf("INITIALIZING SEARCH...\n");
	#endif

	// start search key in the generated tree
	begin = clock();
		search_in_tree(search_key, &root, analysis);
	analysis->tempo_pesquisa = (double) (clock() - begin)/CLOCKS_PER_SEC;

	return analysis;
}

void init_node(Node** no){
	*no = NULL;
}

void printRec(Node* p, int nivel){
	if (p == NULL) return;

	if(p->type == INTERNAL){
		printf("LEVEL: %d\n", nivel);
		nivel++;
		for(int i=0 ; i<p->pag.internal.quant ; i++){
			printf("%*s KEY %d\n", 4*(nivel-1), "", p->pag.internal.keys[i]);
			printRec(p->pag.internal.pointers[i], nivel);
			printRec(p->pag.internal.pointers[i+1], nivel);
		}
	}

	if (p->type == LEAF){
		printf("%*s", 4*nivel, "");
		for(int i=0 ; i<p->pag.external.quant ; i++){
			printf("%d ",p->pag.external.registers[i].key);
			//printRegister(&p->pag.external.registers[i]);
		}
		putchar('\n');
	}
}
void printTree(Node* p){
	int  n = 0;
	printRec(p, n);
	printf("\n");
}
