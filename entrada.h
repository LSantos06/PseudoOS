#include <iostream>
#include <list>
#include "processos.h"
#include "arquivos.h"

class ArqInfoProcessos{
    std::list<Processo> processos;

public:
    void foo();
        
};

class ArqOpsSistemasArquivos{
    int qtd_blocos_disco;
    int qtd_segmentos_ocupados_disco;
    std::list<Arquivo> arquivos;
    std::list<Operacao> operacaos;

public:
    void foo();
        
};

