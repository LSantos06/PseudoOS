#ifndef _arquivosH
#define _arquivosH

#include "listaArquivosOperacoes.h"

// Codigos retornados ao realizar uma operacao no sistema de arquivos
typedef enum {
    OPERACAO_NAO_REALIZADA = 0,
    CRIAR_SUCESSO = 1,
    CRIAR_FALHA = -1,
    DELETAR_SUCESSO = 2,
    DELETAR_FALHA = -2,
    OPERACOES_REALIZADAS = 3
} codigos;

// Elemento de disco
typedef struct disco
{
    int nBlocos;
    int nSegmentosOcupados;
    ListaArquivo *arquivos;
    ListaOperacao *operacoes;
    ListaOperacao *realizadas;
    
} Disco;

// Header das funcoes de disco
Disco* montarDisco(char *);
void desmontarDisco(Disco *);
void imprimirDisco(Disco *);
int realizarOperacao(Disco *, int, int);
int realizarOperacoes(Disco *, int, int);
int criarArquivo(Disco *, char, int, int);
int deletarArquivo(Disco *, char, int, int);
void imprimirBlocos(Disco *);

#endif
