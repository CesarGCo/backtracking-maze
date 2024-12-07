#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../fileReader/fileReader.h"

#ifndef MAZE_GENERATOR_H
#define MAZE_GENERATOR_H

void create_maze(DadosLidos *dados, int linhas, int colunas, int numero_chaves_chao, int numero_chaves_inicial, int numero_portas);

#endif