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