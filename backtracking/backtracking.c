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


labirinto cria_labirinto(FILE *arquivo) {
    labirinto lab;
    aluno aluno;
    aluno.movimentos = 0;


    fscanf(arquivo, "%d %d %d", &lab.largura, &lab.altura, &aluno.chaves); 

    lab.aluno = aluno; 

    lab.matriz = malloc(lab.altura * sizeof(celula *));
    for (int i = 0; i < lab.altura; i++) {
        lab.matriz[i] = malloc(lab.largura * sizeof(celula));
        for (int j = 0; j < lab.largura; j++) {
            char ch;
            do {
                ch = fgetc(arquivo);
            } while (ch == '\n' || ch == ' ');

            if (ch == '0') {
                lab.matriz[i][j].tipo = ch;
                lab.matriz[i][j].visitada = true;
                lab.inicio_largura = j;
                lab.inicio_altura = i;
            } else {
                lab.matriz[i][j].tipo = ch;
                lab.matriz[i][j].visitada = false;
            }
        }
    }

    return lab;
}


void exibe_labirinto(labirinto lab) {
    for (int i = 0; i < lab.altura; i++) {
        for (int j = 0; j < lab.largura; j++) {
            switch (lab.matriz[i][j].tipo) {
                case '0': // Verde: Estudante inicialmente
                    printf("\033[0;32m[0]\033[0m");
                    break;
                case '1': // Branco: Célula vazia
                    printf("\033[0;37m[1]\033[0m");
                    break;
                case '2': // Azul: Parede
                    printf("\033[0;34m[2]\033[0m");
                    break;
                case '3': // Vermelho
                    printf("\033[0;31m[3]\033[0m");
                    break;
                case '5': // Amarelo: Célula com chave
                    printf("\033[0;33m[5]\033[0m");
                    break;
                default: // Caso não mapeado, exibir normalmente
                    printf("[ ]");
                    break;
            }
        }
        printf("\n");
    }
}


int direcoes[4][2] = {
    {-1, 0},  // cima
    {0, -1},  // esquerda
    {0, 1},   // direita
    {1, 0}    // baixo
};

// Função para verificar se uma célula é válida para o movimento (não altera estado)
bool valida_movimento(int x, int y, labirinto *lab) {
    if (x >= 0 && x < lab->altura && y >= 0 && y < lab->largura) {
        if (lab->matriz[x][y].tipo == '2' || lab->matriz[x][y].visitada) {
            return false; // Parede ou célula já visitada
        }
        if (lab->matriz[x][y].tipo == '3' && lab->aluno.chaves <= 0) {
            return false; // Não pode passar por célula vermelha sem chaves
        }
        return true; // Movimento válido
    }
    return false; // Fora dos limites
}

// Função para verificar se não há mais movimentos possíveis
bool sem_movimentos(int x, int y, labirinto *lab) {
    for (int i = 0; i < 4; i++) {
        int novo_x = x + direcoes[i][0];
        int novo_y = y + direcoes[i][1];
        // Verifica se há pelo menos um movimento válido
        if (valida_movimento(novo_x, novo_y, lab)) {
            return false;
        }
    }
    return true; // Nenhum movimento possível
}

// Função de backtracking para andar pelo labirinto
bool backtrack(int x, int y, labirinto *lab) {
    // Se a célula está na linha 0, o estudante escapou
    if (x == 0) {
        printf("Escapou do labirinto na linha 0, posição coluna %d, linha %d com %d movimentos\n", x, y, lab->aluno.movimentos);
        lab->matriz[x][y].tipo = '0'; 
        return true;
    }

    // Marca a célula atual como visitada
    lab->matriz[x][y].visitada = true;
    lab->aluno.movimentos++;

    // Se a célula é do tipo '5', o aluno pega uma chave
    if (lab->matriz[x][y].tipo == '5') {
        lab->aluno.chaves++;
        printf("Encontrou uma chave! Chaves disponíveis: %d\n", lab->aluno.chaves);
    }

    lab->matriz[x][y].tipo = '0'; // Marca como visitada no labirinto visual
    printf("Movido para coluna %d, linha %d, com %d movimentos\n", y, x, lab->aluno.movimentos);

    // Verifica se está cercado e não há movimentos possíveis
    if (sem_movimentos(x, y, lab)) {
        printf("Sem movimentos possíveis a partir da coluna %d, linha%d. Labirinto sem solução.\n", y, x);
        return false;
    }

    // Explora as 4 direções possíveis (cima, esquerda, direita, baixo)
    for (int i = 0; i < 4; i++) {
        int novo_x = x + direcoes[i][0];
        int novo_y = y + direcoes[i][1];

        if (valida_movimento(novo_x, novo_y, lab)) {
            // Se for uma célula vermelha, consome uma chave antes de mover
            if (lab->matriz[novo_x][novo_y].tipo == '3') {
                lab->aluno.chaves--;
                printf("Gastou uma chave! Chaves restantes: %d\n", lab->aluno.chaves);
            }

            if (backtrack(novo_x, novo_y, lab)) {
                return true; // Caminho para a solução encontrado
            }

            // Se não deu certo, devolve a chave gasta ao voltar
            if (lab->matriz[novo_x][novo_y].tipo == '3') {
                lab->aluno.chaves++;
                printf("Recuperou uma chave! Chaves disponíveis: %d\n", lab->aluno.chaves);
            }
        }
    }

    // Retrocede (backtrack) se nenhuma solução for encontrada
    lab->matriz[x][y].visitada = false;
    return false;
}
