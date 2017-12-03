#ifndef _listaArquivosOperacaoH
#define _listaArquivosOperacaoH

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

// Headers das funcoes de lista/tabela de arquivos
ListaArquivo* criarListaArquivo();
ListaArquivo* inserirListaArquivo(ListaArquivo *, char, int, int, int);
int vazioListaArquivo(ListaArquivo *);
void desalocarListaArquivo(ListaArquivo *);
void imprimirListaArquivo(ListaArquivo *);

// Headers das funcoes de lista/tabela de operacoes
ListaOperacao* criarListaOperacao(); 
ListaOperacao* inserirListaOperacao(ListaOperacao *, int, int, char, int, int);
int vazioListaOperacao(ListaOperacao *);
void desalocarListaOperacao(ListaOperacao *);
void imprimirListaOperacao(ListaOperacao *);

#endif
