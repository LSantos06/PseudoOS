#include <stdio.h>
#include <stdlib.h>
#include "arquivos.h"
#include "processos"


// Elemento da lista/tabela de processos
typedef struct processo
{
    int tempoInicializacao;
    int prioridade;
    int tempoProcessador;
    int nBlocosMemoria;
    int nCodigoImpressora;
    int requisicaoScanner;
    int requisicaoModem;
    int nCodigoDisco;
} Processo;
