#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    char tipo;    // Tipo da célula (parede, caminho, etc.)
    bool visitada; // Se a célula já foi visitada
} celula;

typedef struct {
    int chaves; // Número de chaves do aluno
    int movimentos; // Número de movimentos do aluno
} aluno;

typedef struct {
    celula **matriz; // Matriz do labirinto
    int largura;     // Largura do labirinto
    int altura;      // Altura do labirinto
    aluno aluno;
    int inicio_largura;
    int inicio_altura;
} labirinto;


labirinto cria_labirinto(FILE *arquivo);
void exibe_labirinto(labirinto labirinto);
bool valida_movimento(int x, int y, labirinto *lab);
bool backtrack(int x, int y, labirinto *lab);