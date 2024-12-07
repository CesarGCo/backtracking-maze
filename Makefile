# Variáveis para o compilador e flags
CC = gcc
CFLAGS = -Wall

# Valor padrão para ANALISE (se necessário)
ANALISE ?= 0

# Regra para compilar os arquivos
All: main.c fileReader/fileReader.c backtracking/backtracking.c menu/menu.c mazeGenerator/maze_generator.c
	$(CC) $(CFLAGS) -DANALISE=$(ANALISE) main.c fileReader/fileReader.c backtracking/backtracking.c menu/menu.c mazeGenerator/maze_generator.c -o exec

# Regra para executar o código após compilar
Run: All
	./exec

# Tornar o alvo padrão o "Run"
.DEFAULT_GOAL := Run

# Regra para limpar os arquivos gerados
clean:
	rm -f exec
