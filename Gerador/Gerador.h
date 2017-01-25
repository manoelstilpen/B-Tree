#ifndef TP1_GERADOR_H_
#define TP1_GERADOR_H_

#include "../Commons.h"

#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>

void generateRandomString(char*, int);
void fillRegisters(Registro*, int, int);
void fillRegistersFile(Registro*, int, char *);
void shakePositions(Registro*, int );
void generateRegisters(int, int, char*, int);

#endif