#ifndef FILE_READER
#define FILE_READER

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../common.h"

typedef struct {
    int num_chaves;
    int **matriz_labirinto;
    int tamanho_linha;
    int tamanho_coluna;
    bool esta_carregado;
} DadosLidos;

DadosLidos le_arquivo(char *caminho);

void libera_matriz(DadosLidos *dado);
int **copia_matriz(int **original, int linhas, int colunas);
void exibe_labirinto(int **labirinto, int linhas, int colunas);

#endif