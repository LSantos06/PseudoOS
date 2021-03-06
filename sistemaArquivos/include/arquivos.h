#ifndef ARQUIVOS_H
#define ARQUIVOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Codigos retornados ao realizar uma operacao no sistema de arquivos
typedef enum {
    OPERACAO_NAO_REALIZADA = 0,
    CRIAR_SUCESSO = 1,
    CRIAR_FALHA = -1,
    DELETAR_SUCESSO = 2,
    DELETAR_FALHA = -2,
    OPERACOES_REALIZADAS = 3
} codigos;

// Elemento da lista/tabela de arquivos
typedef struct listaArquivo
{
    char nomeArquivo;
    int nPrimeiroBloco;
    int nBlocosOcupados;
    int idProcesso;
    struct listaArquivo *proximo;
} ListaArquivo;

// Elemento da lista/tabela de operacoes
typedef struct listaOperacao
{
    int idProcesso;
    int codigoOperacao;
    char nomeArquivo;
    int nBlocosCriar;
    int estado;
    struct listaOperacao *proxima;
} ListaOperacao;

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
void relatorioOperacoes(Disco *);
void imprimirBlocos(Disco *);

// Headers das funcoes de lista/tabela de arquivos
ListaArquivo* criarListaArquivo();
ListaArquivo* inserirListaArquivo(ListaArquivo *, char, int, int, int);
void desalocarListaArquivo(ListaArquivo *);
void imprimirListaArquivo(ListaArquivo *);

// Headers das funcoes de lista/tabela de operacoes
ListaOperacao* criarListaOperacao();
ListaOperacao* inserirListaOperacao(ListaOperacao *, int, int, char, int, int);
void desalocarListaOperacao(ListaOperacao *);
void imprimirListaOperacao(ListaOperacao *);

#endif
