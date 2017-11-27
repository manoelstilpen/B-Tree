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

#ifndef TP1_ARVOREB2_H_
#define TP1_ARVOREB2_H_

#include "Commons.h"
#include "time.h"
#include "stdio.h"
#include <stdlib.h>

#define ORDER 4
#define ORDER_LEAF ORDER*2

enum {INTERNAL, LEAF};

typedef struct Node{
	int type;

	union {
		struct {
			int quant;
			int keys[ORDER+1];
			struct Node* pointers[ORDER+2];
		} internal;

		struct {
			int quant;
			Registro registers[ORDER_LEAF];
		} external;

	} pag;

} Node;

void init_node(Node**);

void insertRegisterInArray(Registro*, Node**, Analise*);
void insertKeyInArray(int, Node**, Analise*);
void insertPointerInArray(Node*, Node**, Analise*);

void insert_register(Registro*, Node**, Analise*);
void insert_in_tree(Registro*, Node*, int*, Node**, int*, Analise*);
void search_int_tree(int, Node** Ap, Analise*);
Analise* run_bPlus_tree(char*, int);

void printTree(Node*);
void printRec(Node*, int);

#endif
