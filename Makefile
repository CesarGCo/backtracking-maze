# Variáveis para o compilador e flags
CC = gcc
CFLAGS = -Wall

# Valor padrão para ANALISE (se necessário)
ANALISE ?= 0

All: main.c fileReader/fileReader.c backtracking/backtracking.c menu/menu.c
	$(CC) $(CFLAGS) -DANALISE=$(ANALISE) main.c -o exec fileReader/fileReader.c backtracking/backtracking.c menu/menu.c

Run: All
	./exec

clean:
	rm -f exec
