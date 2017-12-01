#include <iostream>
#include <list>
#include "processos.h"
#include "arquivos.h"

using namespace std;

class ArqInfoProcessos{
public:    
    list<Processo> processos;
    void foo();
        
};

class ArqOpsSistemasArquivos{
public:    
    int qtd_blocos_disco;
    int qtd_segmentos_ocupados_disco;
    list<Arquivo> arquivos;
    list<Operacao> operacaos;
    void foo();
        
};

