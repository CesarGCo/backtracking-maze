#ifndef COMMON_H
#define COMMON_H

// O ifdef abaixo verifica o sistema operacional, para 
// incluir a biblioteca corretamente
#ifdef __unix__         
    #include <unistd.h>

#elif defined(_WIN32) || defined(WIN32) 

   #define OS_Windows

   #include <windows.h>

#endif

// Definindo cores utilizadas no código:
#define RED "\x1b[31m"
#define WHITE "\x1b[37m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define GREEN "\e[0;32m"
#define RESET "\033[0m"

//Incluindo Bibliotecas padrão:
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#endif