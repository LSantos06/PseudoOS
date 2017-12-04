#ifndef PROCESSOS_H
#define PROCESSOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Elemento da lista/tabela de processo
typedef struct listaProcesso
{
    int idProcesso;
    int tempoInicializacao;
    int prioridade;
    int tempoProcessador;
    int blocosMemoria;
    int nCodigoImpressora;
    int requisicaoScanner;
    int requisicaoModem;
    int nCodigoDisco;
    struct listaProcesso *proximo;
} ListaProcesso;

// Header da função de montar lista/tabela de processos
ListaProcesso* montarListaProcesso(char *);

// Headers das funcoes de lista/tabela de processos
ListaProcesso* criarListaProcesso();
ListaProcesso* inserirListaProcesso(ListaProcesso *, int, int, int, int, int, int, int, int, int);
void desalocarListaProcesso(ListaProcesso *);
void imprimirListaProcesso(ListaProcesso *);

#endif
