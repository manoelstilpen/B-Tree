#include "B+Tree.h"
#include "Commons.h"
#include "Gerador/Gerador.h"

#include "stdio.h"

void usage(){
	printf("USAGE:\n");
	printf("-n name [REGISTER FILE NAME]\n-p x [SEARCH FOR x KEY]\n");
	printf("-g x [GENERATE x NEW REGISTERS]\n-o (c,d,a) [GENERATION FILE ORDER]\n");
	printf("-P [SHOW REGISTERS IN FILE]\n");
	exit(EXIT_FAILURE);
}

void convertParameters(char* order_aux, int* order){

	if(strcmp(order_aux, "c") == 0 || strcmp(order_aux, "C") == 0){
		*order = CRESCENTE;
	} else if(strcmp(order_aux, "d") == 0 || strcmp(order_aux, "D") == 0){
		*order = DECRESCENTE;
	} else if(strcmp(order_aux, "a") == 0 || strcmp(order_aux, "A") == 0){
		*order = ALEATORIO;
	} else {
		printf("UNKNOWN ORDER!\n");
		*order = -1;
	}
}

int main(int argc, char** argv){

	int opt;

	int search = false;
	int generate = false;
	int show = false;

	int registersQuantity = 0;
	char* order_aux = "c";
	char* registersFileName = "arquivo.bin";
	int search_key = 0;
	extern char *optarg;

	int order = CRESCENTE;

	Analise* analysis = init_analysis();

	clock_t begin;

	if(argc == 1){
		usage();
	}

	while ((opt = getopt(argc, argv, "p:n:g:o:hP")) != -1) {
		switch(opt){
			case 'p':{
				search_key = (int) atoi(optarg);
				#ifdef PRINT
					printf("SEARCH KEY: %d\n", search_key);
				#endif
				search = true;
				break;
			};
			case 'n':{
				registersFileName = optarg;
				#ifdef PRINT
					printf("FILE NAME: %s\n", registersFileName);
				#endif
				break;
			};
			case 'g':{
				registersQuantity = (int) atoi(optarg);
				generate = true;
				#ifdef PRINT
					printf("GENERATE %d NEW REGISTERS\n", registersQuantity);
				#endif
				break;
			};
			case 'o':{
				order_aux = optarg;
				#ifdef PRINT
					printf("ORDER GENERATION: %s\n", order_aux);
				#endif
				break;
			};
			case 'P':{
				show = true;
				#ifdef PRINT
					printf("EXIBIR REGISTROS: TRUE\n");
				#endif
				break;
			};
			case 'h':{
				usage();
			};
			default:{
	            usage();
        	};
		}
	}

	convertParameters(order_aux, &order);

	#ifdef PRINT
		printf("\n");
	#endif

	if(generate == true){
		generateRegisters(registersQuantity, order, registersFileName, show);
	}

	if(search == true){
		analysis = run_bPlus_tree(registersFileName, search_key);
		printAnalysis(analysis);
	}

	exit(EXIT_SUCCESS);
}