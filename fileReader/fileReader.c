#include "fileReader.h"

DadosLidos le_arquivo(char *caminho){
    DadosLidos dado = {0, NULL, 0, 0, false};
    FILE *arquivo = fopen(caminho, "r");

    if(arquivo == NULL){
        printf("Nao foi possivel abrir o arquivo "RED"%s"RESET"\n",caminho);
        dado.num_chaves = 0;
        dado.matriz_labirinto = NULL;
        return dado;
    }

    
    fscanf(arquivo, "%d %d %d", &dado.tamanho_linha, &dado.tamanho_coluna, &dado.num_chaves);

    
    dado.matriz_labirinto = (int **)malloc(dado.tamanho_linha * sizeof(int *));
    for(int i = 0; i < dado.tamanho_linha; i++){
        dado.matriz_labirinto[i] = (int *)malloc(dado.tamanho_coluna * sizeof(int));
    }

    for(int i = 0; i < dado.tamanho_linha; i++){
        for(int j = 0; j < dado.tamanho_coluna; j++){
            fscanf(arquivo, "%1d", &dado.matriz_labirinto[i][j]);
        }
    }

    fclose(arquivo);
    dado.esta_carregado = true;
    return dado;
}


void libera_matriz(DadosLidos *dado) {
    for (int i = 0; i < dado->tamanho_linha; i++) {
        free(dado->matriz_labirinto[i]);
    }
    free(dado->matriz_labirinto);
    dado->matriz_labirinto = NULL;
}

int **copia_matriz(int **original, int linhas, int colunas) {
    int **copia = malloc(linhas * sizeof(int *));
    for (int i = 0; i < linhas; i++) {
        copia[i] = malloc(colunas * sizeof(int));
        for (int j = 0; j < colunas; j++) {
            copia[i][j] = original[i][j];
        }
    }
    return copia;
}

#include <stdio.h>


void exibe_labirinto(int **labirinto, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (labirinto[i][j] == 0) {
                printf(RED "[0]" RESET);
            } else if (labirinto[i][j] == 1) {
                printf(WHITE "[1]" RESET);
            } else if (labirinto[i][j] == 3) {
                printf(RED "[3]" RESET);
            } else if (labirinto[i][j] == -1) {
                printf(GREEN "[-]" RESET);
            } else {
                printf(BLUE "[%d]" RESET, labirinto[i][j]);
            }
        }
        printf("\n");
    }
}
