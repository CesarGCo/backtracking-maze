#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void esperar_usuario() {
    printf("\nPressione qualquer tecla para retornar ao menu...");
    getchar();
    getchar();
}

void exibir_menu(int isAnalise) {
    DadosLidos dado = {0};
    int opcao;
    char caminho[100];
    int verifica_back = 0;
    int **copia_labirinto = NULL;

    do {
        #ifdef OS_Windows
            system("cls");
        #else
            system("clear");
        #endif 

        menu(isAnalise);
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: 
                printf("| Digite o caminho do arquivo: ");
                scanf("%s", caminho);

                dado = le_arquivo(caminho);
                if (dado.esta_carregado) {
                    printf("| Labirinto carregado com " GREEN "SUCESSO" RESET ".\n");
                } else {
                    printf("| Erro ao carregar o arquivo. Verifique o caminho e tente novamente.\n");
                }
                esperar_usuario();
                break;

            case 2:
                if (!dado.esta_carregado) {
                    printf("| Por favor, carregue um arquivo antes de executar!\n");
                    esperar_usuario();
                    break;
                }

                copia_labirinto = copia_matriz(dado.matriz_labirinto, dado.tamanho_linha, dado.tamanho_coluna);
                int encontrou_saida = 0;
                inicia_backtracking(dado, isAnalise, copia_labirinto, &encontrou_saida);
                if (!encontrou_saida) {
                    printf("| O labirinto " RED "NAO" RESET " possui saída!\n");
                } else {
                    printf("| Backtracking executado com " GREEN "SUCESSO" RESET ".\n");
                }
                verifica_back = 1;
                esperar_usuario();
                break;

            case 3:
                if (verifica_back != 1) {
                    printf("| Backtracking ainda " RED "NAO" RESET " foi feito!\n");
                } else {
                    exibe_labirinto(copia_labirinto, dado.tamanho_linha, dado.tamanho_coluna);
                }
                esperar_usuario();
                break;

            default:
                printf("| Saindo...\n");
                exit(0);
        }
    } while (1);
}

void menu(int isAnalise) {
    printf("|=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=|\n");
    printf("|                 " BLUE "MENU" RESET "                  |\n");
    printf("|         MODO ANALISE ");
    if (isAnalise) printf(GREEN "ATIVADO          " RESET "|\n");
    else printf(RED "DESATIVADO       " RESET "|\n");
    printf("|=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=|\n");
    printf("| Escolha uma das opcoes:               |\n");
    printf("|   1 - Carregar novo arquivo de dados  |\n");
    printf("|   2 - Processar e exibir resposta     |\n");
    printf("|   3 - Mostrar labirinto               |\n");
    printf("|   Outro - Sair                        |\n");
    printf("|=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=|\n");
    printf("| >>> ");
}
