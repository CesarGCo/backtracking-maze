#include "backtracking.h"

void inicia_backtracking(DadosLidos dado, int isAnalise, int **copia_labirinto, int *encontrou_saida) {
    int contagemRecursividade;
    int i; int j;
    for(i = 0; i < dado.tamanho_linha; i++) {
        for(j = 0; j < dado.tamanho_coluna; j++) {
            if(dado.matriz_labirinto[i][j] == 0) {
                if(isAnalise) contagemRecursividade = 1;
                printf("| "GREEN"INICIO"RESET":\n");
                int chaves_finais = movimenta_estudante(copia_labirinto, dado.tamanho_linha, dado.tamanho_coluna, i, j, dado.num_chaves, &contagemRecursividade, encontrou_saida, 0);
                printf("| "YELLOW"Chaves restantes:"RESET" %d\n", chaves_finais);
                if(isAnalise) {
                    printf("|\n| "BLUE"ANALISE"RESET": \n| >>> Numero de chamadas recursivas realizadas: %i\n", contagemRecursividade);
                }
                return;
            }
        }
    }
    (*encontrou_saida) = 1;
    printf("| A posicao inicial do estudante "RED"NAO"RESET" foi encontrada!\n");
    return;
}

int movimenta_estudante(int **labirinto, int linhas, int colunas, int x, int y, int chaves, int* contagemRecursividade, int* encontrou_saida, int chaves_coletadas) {
    if (x == 0) {
        printf("| Linha: %d Coluna: %d\n", x, y);
        printf("| "GREEN"FIM"RESET": O estudante chegou na coluna %d da primeira linha\n", y);
        labirinto[x][y] = -1;
        *encontrou_saida = 1;
        return chaves;
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
                int result = movimenta_estudante(labirinto, linhas, colunas, nx, ny, chaves, contagemRecursividade, encontrou_saida, chaves_coletadas);
                if (result >= 0) return result;
            }
            else if (labirinto[nx][ny] == 3 && chaves > 0) {
                printf("| "BLUE"Usando chave para abrir porta na linha %d, coluna %d"RESET"\n", nx, ny);
                if (*contagemRecursividade > 0) (*contagemRecursividade)++;
                int result = movimenta_estudante(labirinto, linhas, colunas, nx, ny, chaves - 1, contagemRecursividade, encontrou_saida, chaves_coletadas);
                if (result >= 0) return result;
            }
            else if (labirinto[nx][ny] == 4) {
                printf("| "GREEN"Encontrou chave na linha %d, coluna %d"RESET"\n", nx, ny);
                if (*contagemRecursividade > 0) (*contagemRecursividade)++;
                labirinto[nx][ny] = 1;  
                int result = movimenta_estudante(labirinto, linhas, colunas, nx, ny, chaves + 1, contagemRecursividade, encontrou_saida, chaves_coletadas + 1);
                if (result >= 0) return result;
                
                printf("| "RED"Deixando a chave de volta na linha %d, coluna %d"RESET"\n", nx, ny);
                labirinto[nx][ny] = 4;
            }
        }
    }

    labirinto[x][y] = celula_original;
    return -1;
}