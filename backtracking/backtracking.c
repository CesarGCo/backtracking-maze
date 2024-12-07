#include "backtracking.h"

void inicia_backtracking(DadosLidos dado, int isAnalise, int **copia_labirinto, int *encontrou_saida) {
    int contagemRecursividade;
    int i; int j;
    for(i = 0; i < dado.tamanho_linha; i++) {
        for(j = 0; j < dado.tamanho_coluna; j++) {
            if(dado.matriz_labirinto[i][j] == 0) {
                if(isAnalise) contagemRecursividade = 1;
                 printf("| "GREEN"INICIO"RESET":\n");
                movimenta_estudante(copia_labirinto, dado.tamanho_linha, dado.tamanho_coluna, i, j, dado.num_chaves, &contagemRecursividade, encontrou_saida);
                if(isAnalise) {
                    printf("|\n| "BLUE"ANALISE"RESET": \n| >>> Numero de chamadas recursivas realizadas: %i\n", contagemRecursividade);
                }
                return;
            }
        }
    }
    (*encontrou_saida) = 1;
    printf("| A posicao inicial do estudante "RED"NAO"RESET" foi encontrda!\n");
    return;
}

int movimenta_estudante(int **labirinto, int linhas, int colunas, int x, int y, int chaves, int* contagemRecursividade, int* encontrou_saida) {
    if (x == 0) {
        printf("| Linha: %d Coluna: %d\n", x, y);
        printf("| "GREEN"FIM"RESET": O estudante chegou na coluna %d da primeira linha\n", y);
        labirinto[x][y] = -1;
        *encontrou_saida = 1;
        return 1;
    }

    int celula_original = labirinto[x][y];
    labirinto[x][y] = -1;
    printf("| Linha: %d Coluna: %d\n", x, y);

    int direcoes[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

    for (int i = 0; i < 4; i++) {
        int nx = x + direcoes[i][0];
        int ny = y + direcoes[i][1];

        if (nx >= 0 && nx < linhas && ny >= 0 && ny < colunas) {
            if (labirinto[nx][ny] == 1) {
                if (*contagemRecursividade > 0) (*contagemRecursividade)++;
                if (movimenta_estudante(labirinto, linhas, colunas, nx, ny, chaves, contagemRecursividade, encontrou_saida)) {
                    return 1; 
                }
            }
            else if (labirinto[nx][ny] == 3 && chaves > 0) {
                if (*contagemRecursividade > 0) (*contagemRecursividade)++;
                if (movimenta_estudante(labirinto, linhas, colunas, nx, ny, chaves - 1, contagemRecursividade, encontrou_saida)) {
                    return 1; 
                }
            }
            else if (labirinto[nx][ny] == 4) {
                if (*contagemRecursividade > 0) (*contagemRecursividade)++;
                labirinto[nx][ny] = 1;
                if (movimenta_estudante(labirinto, linhas, colunas, nx, ny, chaves + 1, contagemRecursividade, encontrou_saida)) {
                    return 1;
                }
                labirinto[nx][ny] = 4;
            }
        }
    }

    labirinto[x][y] = celula_original;
    return 0;
}




