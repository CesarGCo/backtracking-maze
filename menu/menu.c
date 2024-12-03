#include "menu.h"

void exibir_menu(int isAnalise) {
    DadosLidos dado;
    int opcao;
    char caminho[100];
    int verifica_back = 0;
    int ** copia_labirinto;

    do {
        menu(isAnalise);
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: 
                printf("| Digite o caminho do arquivo: ");
                scanf("%s", caminho);

                dado = le_arquivo(caminho);
                if(dado.esta_carregado == true){
                    printf("| Labirinto carregado com "GREEN"SUCESSO"RESET".\n");
                }
                break;
            
            case 2:
                if (dado.esta_carregado == false) {
                    printf("| Por favor, carregue um arquivo antes de executar!\n");
                    break;
                }
                copia_labirinto = copia_matriz(dado.matriz_labirinto, dado.tamanho_linha, dado.tamanho_coluna);
                int encontrou_saida = 0;
                inicia_backtracking(dado, isAnalise, copia_labirinto, &encontrou_saida);
                if(!encontrou_saida){
                    printf("| O labirinto "RED"NAO"RESET" possui saida!\n");
                }
                verifica_back = 1;
                break;

            case 3:
                if(verifica_back != 1){
                    printf("| Backtracking ainda "RED"NAO"RESET" foi feito!\n");
                } else {
                    exibe_labirinto(copia_labirinto, dado.tamanho_linha, dado.tamanho_coluna);
                }
                break;
            case 4:
                printf("| Saindo...\n");
                exit(0);
                return;

            default:
                printf("| "RED"Opcao invalida!\n"RESET);
                break;
        }
        system("pause");
        #ifdef OS_Windows
            /* Codigo Windows */
            system("cls");
        #else
            /* Codigo GNU/Linux */
            system("clear");
        #endif 
    } while (1);
}

void menu(int isAnalise) {
    printf("|=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=|\n");
    printf("|                 "BLUE"MENU"RESET"                  |\n");
    printf("|         MODO ANALISE ");
    if(isAnalise) printf(GREEN"ATIVADO          "RESET"|\n");
    else printf(RED"DESATIVADO       "RESET"|\n");
    printf("|=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=|\n");
    printf("| Escolha uma das opcoes:               |\n");
    printf("|   1 - Carregar arquivo do labirinto   |\n");
    printf("|   2 - Executar backtracking           |\n");
    printf("|   3 - Mostrar matriz                  |\n");
    printf("|   4 - Sair                            |\n");
    printf("|=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=|\n");
    printf("| >>> ");
}