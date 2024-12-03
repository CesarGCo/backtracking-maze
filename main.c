#include "common.h"
#include "./fileReader/fileReader.h"
#include "./menu/menu.h"

#ifndef ANALISE
#define ANALISE 0
#endif 
int main() {

    exibir_menu(ANALISE);
    
    //DadosLidos dado = le_arquivo("input.txt");

    return 0;
}