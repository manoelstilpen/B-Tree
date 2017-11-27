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
#include "Commons.h"
#include "Gerador/Gerador.h"

#include "stdio.h"

void usage(){
	printf("USAGE:\n");
	printf("-n name [REGISTER FILE NAME]\n-p x [SEARCH FOR x KEY]\n");
	printf("-g x [GENERATE x NEW REGISTERS]\n-o (r,d,a) [GENERATION FILE ORDER]\n");
	printf("-P [SHOW REGISTERS IN FILE]\n");
	exit(EXIT_FAILURE);
}

void convertParameters(char* order_aux, int* order){

	if(strcmp(order_aux, "a") == 0 || strcmp(order_aux, "A") == 0){
		*order = ASCENDING;
	} else if(strcmp(order_aux, "d") == 0 || strcmp(order_aux, "D") == 0){
		*order = DESCENDING;
	} else if(strcmp(order_aux, "r") == 0 || strcmp(order_aux, "R") == 0){
		*order = RANDOM;
	} else {
		printf("UNKNOWN ORDER!\n");
		*order = -1;
	}
}

int main(int argc, char** argv){

	int opt;

	// standart values - initializing

	int search = false;
	int generate = false;
	int show = false;

	int registersQuantity = 0;
	char* order_aux = "c";
	char* registersFileName = "arquivo.bin";
	int search_key = 0;
	extern char *optarg;

	int order = ASCENDING;
	clock_t begin;

	Analise* analysis = init_analysis();

	if(argc == 1){
		usage();
	}

    // parse command line arguments
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
					printf("SHOW REGISTERS: TRUE\n");
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

    // generate instance file for benchmark
	if(generate == true){
		generateRegisters(registersQuantity, order, registersFileName, show);
	}

    // begins the search
	if(search == true){
		analysis = run_bPlus_tree(registersFileName, search_key);
		printAnalysis(analysis);
	}

	exit(EXIT_SUCCESS);
}
