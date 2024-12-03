#include <stdio.h>
#include "menu.h"

void exibir_menu() {
    DadosLidos dado;
    int opcao;
    char caminho[100];
    int **copia_labirinto;
    int verifica_back = 0;

    do {
        printf(RED "\nMENU:\n" WHITE);
        printf("1) Carregar arquivo do labirinto\n");
        printf("2) Executar backtracking\n");
        printf("3) Mostrar matriz\n");
        printf("4) Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: 
                printf("Digite o caminho do arquivo: ");
                scanf("%s", caminho);

                dado = le_arquivo(caminho);
                printf("Labirinto carregado com sucesso!\n");
                break;
            
            case 2:
                if (dado.matriz_labirinto == NULL) {
                    printf("Por favor, carregue um arquivo antes de executar.\n");
                    break;
                }

                copia_labirinto = copia_matriz(dado.matriz_labirinto, dado.tamanho_linha, dado.tamanho_coluna);
                movimenta_estudante(copia_labirinto, dado.tamanho_linha, dado.tamanho_coluna, 9, 4, dado.num_chaves, 0);
                verifica_back = 1;
                break;

            case 3:
                if(verifica_back != 1){
                    printf("Backtracking ainda não foi feito!");
                } else {
                    exibe_labirinto(copia_labirinto, dado.tamanho_linha, dado.tamanho_coluna);
                }
                break;
            case 4:
                printf("Saindo...\n");
                exit(0);
                return;

            default:
                printf("Opção inválida.\n");
                break;
        }
    } while (1);
}

