#include "maze_generator.h"

void create_maze(DadosLidos *dados, int linhas, int colunas, int numero_chaves_chao, int numero_chaves_inicial, int numero_portas) {
    srand(time(NULL));
    dados->matriz_labirinto = malloc(linhas * sizeof(int *));
    for (int i = 0; i < linhas; i++) {
        dados->matriz_labirinto[i] = malloc(colunas * sizeof(int));
        for (int j = 0; j < colunas; j++) {
            dados->matriz_labirinto[i][j] = 1;
        }
    }

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (rand() % 3 == 0 && j < colunas) {
                dados->matriz_labirinto[i][j] = 2;
            }
        }
    }

    for (int k = 0; k < numero_portas; k++) {
        int x, y;
        do {
            x = rand() % linhas;
            y = rand() % colunas;
        } while (!(dados->matriz_labirinto[x][y] == 2 && 
                  ((x > 0 && dados->matriz_labirinto[x - 1][y] == 2) || 
                   (x < linhas - 1 && dados->matriz_labirinto[x + 1][y] == 2) ||
                   (y > 0 && dados->matriz_labirinto[x][y - 1] == 2) || 
                   (y < colunas - 1 && dados->matriz_labirinto[x][y + 1] == 2))));
        dados->matriz_labirinto[x][y] = 3;
    }

    for (int k = 0; k < numero_chaves_chao; k++) {
        int x, y;
        do {
            x = rand() % linhas;
            y = rand() % colunas;
        } while (dados->matriz_labirinto[x][y] != 1);
        dados->matriz_labirinto[x][y] = 4;
    }

    int start_x, start_y;
    do {
        start_x = (linhas - 1) - (rand() % (linhas / 3));
        start_y = rand() % colunas;
    } while (dados->matriz_labirinto[start_x][start_y] != 1);
    dados->matriz_labirinto[start_x][start_y] = 0;

    dados->num_chaves = numero_chaves_inicial;
    dados->tamanho_linha = linhas;
    dados->tamanho_coluna = colunas;
    dados->esta_carregado = true;
}
