#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void esperar_usuario() {
    printf("\nPressione ENTER para retornar ao menu...");
    getchar();
    getchar();
}

void exibir_menu(int isAnalise) {
    DadosLidos dado = {0};
    int opcao;
    char caminho[100];
    int verifica_back = 0;
    int **copia_labirinto = NULL;

    //Variaveis do gerador de labirinto
    int numero_linhas;
    int numero_colunas;
    int numero_chaves_chao;
    int numero_chaves_inicial;
    int numero_portas;

    do {
        #ifdef OS_Windows
            //system("cls");
        #else
            //system("clear");
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

            case 4:
                printf("| Digite a quantidade de linhas do labirinto: ");
                scanf("%d", &numero_linhas);
                printf("| Digite a quantidade de colunas do labirinto: ");
                scanf("%d", &numero_colunas);
                printf("| Digite a quantidade de chaves iniciais do estudante: ");
                scanf("%d", &numero_chaves_inicial);
                printf("| Digite a quantidade de chaves que estarao no chao: ");
                scanf("%d", &numero_chaves_chao);
                printf("| Digite a quantidade de portas presentes no labrinto: ");
                scanf("%d", &numero_portas);

                create_maze(&dado, numero_linhas, numero_colunas, numero_chaves_chao, numero_chaves_inicial, numero_portas);
                printf("| Labirinto gerado abaixo: \n");
                exibe_labirinto(dado.matriz_labirinto, dado.tamanho_linha, dado.tamanho_coluna);
                printf("| Se deseja usar o labirinto digite (1) caso contrario digite (2): ");
                int opcao_digitada = 0;
                scanf("%d", &opcao_digitada);
                if(opcao_digitada == 1){
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
                } else if(opcao_digitada == 2){
                    continue;
                }
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
    printf("|   4 - Gerar labirinto                 |\n");
    printf("|   Outro - Sair                        |\n");
    printf("|=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=|\n");
    printf("| >>> ");
}
