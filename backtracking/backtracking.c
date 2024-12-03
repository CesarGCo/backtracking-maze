#include "backtracking.h"

// int pode_mover(DadosLidos dados, int i, int j) {
//     if (i < 0 || i >= dados.tamanho_linha || j < 0 || j >= dados.tamanho_coluna) 
//         return 0;

//     if (dados.matriz_labirinto[i][j] == 2 || dados.matriz_labirinto[i][j] == -1) 
//         return 0;

//     return 1;
// }

// void inicia_backtracking(DadosLidos dados) {
//     for (int i = 0; i < dados.tamanho_linha; i++) {
//         for (int j = 0; j < dados.tamanho_coluna; j++) {
//             if (dados.matriz_labirinto[i][j] == 0) { 
//                 printf("Iniciando o backtracking a partir da posição [%d, %d]\n", i, j);
//                 movimenta_estudante(dados, i, j);
//                 return;
//             }
//         }
//     }

//     printf("Ponto inicial (0) não encontrado no labirinto.\n");
// }

// void movimenta_estudante(DadosLidos dados, int i, int j) {
//     if (i == 0) {
//         printf("Estudante chegou à saída na posição [%d, %d]\n", i, j);
//         return;
//     }

//     dados.matriz_labirinto[i][j] = -1;

//     int movimentos[4][2] = {
//         {-1, 0}, // Cima
//         {1, 0},  // Baixo
//         {0, -1}, // Esquerda
//         {0, 1}   // Direita
//     };

//     for (int k = 0; k < 4; k++) {
//         int nova_linha = i + movimentos[k][0];
//         int nova_coluna = j + movimentos[k][1];

//         if (pode_mover(dados, nova_linha, nova_coluna)) {
//             printf("Movendo para [%d, %d]\n", nova_linha, nova_coluna);
//             movimenta_estudante(dados, nova_linha, nova_coluna);
//         }
//     }

//     dados.matriz_labirinto[i][j] = 1;
// }


int movimenta_estudante(int **labirinto, int linhas, int colunas, int x, int y, int chaves, int passos, int *cont) {
    if (x == 0 || *cont == 10) {
        if (*cont == 10) {
            printf("O labirinto não tem saída.\n");
            return 1;
        }
        printf("Linha: %d Coluna: %d\n", x, y);
        printf("O estudante se movimentou %d vezes e chegou na coluna %d da primeira linha\n", passos, y);
        labirinto[x][y] = -1;
        return 1;
    }

    int valor_atual = labirinto[x][y];
    labirinto[x][y] = -1;
    printf("Linha: %d Coluna: %d\n", x, y);

    if (labirinto[x - 1][y] == 2) {
        (*cont)++;
        if (y > 0 && labirinto[x][y - 1] != 2 && labirinto[x][y - 1] != -1) {
            if (movimenta_estudante(labirinto, linhas, colunas, x, y - 1, chaves, passos + 1, cont)) {
                return 1;
            }
        }

        if (y < colunas - 1 && labirinto[x][y + 1] != 2 && labirinto[x][y + 1] != -1) {
            if (movimenta_estudante(labirinto, linhas, colunas, x, y + 1, chaves, passos + 1, cont)) {
                return 1;
            }
        }

        return 0;
    }

    *cont = 0;

    int direcoes[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    for (int i = 0; i < 4; i++) {
        int nx = x + direcoes[i][0];
        int ny = y + direcoes[i][1];

        if (nx >= 0 && nx < linhas && ny >= 0 && ny < colunas) {
            if (labirinto[nx][ny] == 1 || (labirinto[nx][ny] == 3 && chaves > 0)) {
                int nova_chave = chaves - (labirinto[nx][ny] == 3 ? 1 : 0);
                if (movimenta_estudante(labirinto, linhas, colunas, nx, ny, nova_chave, passos + 1, cont)) {
                    return 1;
                }
            }
        }
    }

    labirinto[x][y] = valor_atual;
    return 0;
}



