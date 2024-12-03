#ifndef FILE_READER
#define FILE_READER

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int num_chaves;
    int **matriz_labirinto;
    int tamanho_linha;
    int tamanho_coluna;
} DadosLidos;

DadosLidos le_arquivo(char *caminho);

void libera_matriz(DadosLidos *dado);

#endif