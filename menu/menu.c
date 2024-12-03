#include <stdio.h>
#include "menu.h"

void exibir_menu() {
    DadosLidos dado;
    int opcao;
    char caminho[100];

    do {
        printf(RED "\nMENU:\n" WHITE);
        printf("1) Carregar arquivo do labirinto\n");
        printf("2) Executar backtracking\n");
        printf("3) Mostrar matriz\n");
        printf("3) Sair\n");
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
                //inicia_backtracking(dado);
                movimenta_estudante(dado.matriz_labirinto, dado.tamanho_linha, dado.tamanho_coluna, 9, 4, dado.num_chaves, 0);
                libera_matriz(&dado);
                break;


            case 3:
                 for (int i = 0; i < 10; i++) {
                    for (int j = 0; j < 10; j++) {
                        printf("%d", dado.matriz_labirinto[i][j]);
                    }
                    printf("\n");
                }
                break;
            case 4:
                printf("Saindo...\n");
               // libera_matriz(&dado);
                return;

            default:
                printf("Opção inválida.\n");
                break;
        }
    } while (1);
}
