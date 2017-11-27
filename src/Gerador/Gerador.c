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

#include "Gerador.h"

//dados para gerar string aleatoria
const char charset[] = "abcdefghijklmnopqrstuvwxyz";
const int sizeVecChar = 26;

void generateRandomString(char* vec, int size){
	for(int i=0 ; i<size ; i++){
		int pos = rand() % sizeVecChar;
		vec[i] = charset[pos];
	}
}

void fillRegisters(Registro* registers, int quantity, int order){

	if(order == ASCENDING){
		for(int i=0 ; i<quantity ; i++){
			registers[i].key = i;
			registers[i].dado1 = rand() % 1000;
			generateRandomString(registers[i].dado2, TAM_CHAR_REGISTRO);
		}

	} else if(order == DESCENDING){
		for(int i=quantity-1 ; i>= 0 ; i--){
			registers[i].key = quantity-i-1;
			registers[i].dado1 = rand() % 1000;
			generateRandomString(registers[i].dado2, TAM_CHAR_REGISTRO);
		}

	} else if(order == RANDOM){

		for(int i=0 ; i<quantity ; i++){
			registers[i].key = i;
			registers[i].dado1 = rand() % 1000;
			generateRandomString(registers[i].dado2, TAM_CHAR_REGISTRO);
		}

		shakePositions(registers, quantity);

	} else {
		printf("OPCAO INVALIDA\n");
	}

}

void shakePositions(Registro* registers, int quantity){
	Registro aux;

	for(int i=0 ; i<quantity ; i++){
		int newpos = rand() % quantity;
		aux = registers[i];
		registers[i] = registers[newpos];
		registers[newpos] = aux;
	}

}

void fillRegisterFile(Registro* registers, int quantity, char* fileRegistersName){
	FILE* file_reg = fopen(fileRegistersName, "w+b");

	for(int i=0 ; i<quantity ; i++){
		fwrite(&(registers[i]), sizeof(Registro), 1, file_reg);
	}

	fclose(file_reg);
}

void generateRegisters(int registersQuantity, int order, char* registersFileName, int show){
	#ifdef PRINT
		printf("%s\n", "GENERATING REGISTERS...");
	#endif

	Registro* registers;

	srand(time(NULL));

	//aloca o vetor de registro
	registers = (Registro*) malloc(sizeof(Registro)*registersQuantity);

	fillRegisters(registers, registersQuantity, order);
	fillRegisterFile(registers, registersQuantity, registersFileName);

	if(show == true){
		printFile(registersFileName);
	}
}
