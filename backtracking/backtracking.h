#include "../common.h"
#include "../fileReader/fileReader.h"

#ifndef BACKTRACKING
#define BACKTRACKING

void inicia_backtracking(DadosLidos dado, int isAnalise, int ** copia_labirinto);

int movimenta_estudante(int **labirinto, int linhas, int colunas, int x, int y, int chaves, int contagemRecursividade);

#endif