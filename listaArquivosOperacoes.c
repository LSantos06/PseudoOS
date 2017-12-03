#include <stdio.h>
#include <stdlib.h>
#include "listaArquivosOperacoes.h"

// Funcoes de lista/tabela de arquivos

// Cria lista/tabela
ListaArquivo* criarListaArquivo()
{
    return NULL;
}

// Insere novo elemento ao final da lista/tabela
ListaArquivo* inserirListaArquivo(ListaArquivo *arquivos, char nomeArquivo, int nPrimeiroBloco, int nBlocosOcupados, int idProcesso)
{
	ListaArquivo *auxListaArquivo = NULL;
	ListaArquivo *novo = (ListaArquivo *)malloc(sizeof(ListaArquivo));

    novo->nomeArquivo = nomeArquivo;
    novo->nPrimeiroBloco = nPrimeiroBloco;
    novo->nBlocosOcupados = nBlocosOcupados;
    novo->idProcesso = idProcesso;
    novo->proximo = NULL;
    if(arquivos != NULL)
    {
        for(auxListaArquivo = arquivos; auxListaArquivo->proximo != NULL; auxListaArquivo = auxListaArquivo->proximo);
        auxListaArquivo->proximo = novo;
    }
    else
        arquivos = novo;
    return arquivos;
}

// Verifica se lista/tabela esta vazia
int vazioListaArquivo(ListaArquivo *arquivos)
{
    if(arquivos == NULL)
        return 1;
    else
        return 0;
}

// Desaloca conteudo da lista/tabela
void desalocarListaArquivo(ListaArquivo *arquivos)
{
    if(!vazioListaArquivo(arquivos))
    {
        desalocarListaArquivo(arquivos->proximo);
        free(arquivos);
    }
    return;
}

// Imprime elementos da lista/tabela
void imprimirListaArquivo(ListaArquivo *arquivos)
{
    if(!vazioListaArquivo(arquivos))
    {
        printf("nomeArquivo: %c | nPrimeiroBloco: %d | nBlocosOcupados: %d | idProcesso: %d\n",arquivos->nomeArquivo,arquivos->nPrimeiroBloco,arquivos->nBlocosOcupados,arquivos->idProcesso);
        imprimirListaArquivo(arquivos->proximo);
    }
    return;
}


// Funcoes de lista/tabela de operacoes

// Cria lista/tabela
ListaOperacao* criarListaOperacao()
{
    return NULL;
}

// Insere novo elemento ao final da lista/tabela
ListaOperacao* inserirListaOperacao(ListaOperacao *operacoes, int idProcesso, int codigoOperacao, char nomeArquivo, int nBlocosCriar, int estado)
{
	ListaOperacao *auxListaOperacao = NULL;
	ListaOperacao *nova = (ListaOperacao *)malloc(sizeof(ListaOperacao));
    nova->idProcesso = idProcesso;
    nova->codigoOperacao = codigoOperacao;
    nova->nomeArquivo = nomeArquivo;
    nova->nBlocosCriar = nBlocosCriar;
    nova->estado = estado;
    nova->proxima = NULL;
    if(operacoes != NULL)
    {
        for(auxListaOperacao = operacoes; auxListaOperacao->proxima != NULL; auxListaOperacao = auxListaOperacao->proxima);
        auxListaOperacao->proxima = nova;
    }
    else
        operacoes = nova;
    return operacoes;
}

// Verifica se lista/tabela esta vazia
int vazioListaOperacao(ListaOperacao *operacoes)
{
    if(operacoes == NULL)
        return 1;
    else
        return 0;
}

// Desaloca conteudo da lista/tabela
void desalocarListaOperacao(ListaOperacao *operacoes)
{
    if(!vazioListaOperacao(operacoes))
    {
        desalocarListaOperacao(operacoes->proxima);
        free(operacoes);
    }
    return;
}

// Imprime elementos da lista/tabela
void imprimirListaOperacao(ListaOperacao *operacoes)
{
    if(!vazioListaOperacao(operacoes))
    {
        printf("idProcesso: %d | codigoOperacao: %d | nomeArquivo: %c | nBlocosCriar: %d | estado: %d\n",operacoes->idProcesso,operacoes->codigoOperacao,operacoes->nomeArquivo,operacoes->nBlocosCriar,operacoes->estado);
        imprimirListaOperacao(operacoes->proxima);
    }
    return;
}
