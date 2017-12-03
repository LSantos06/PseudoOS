// 
typedef enum {
    OPERACAO_NAO_REALIZADA = 0,
    CRIAR_SUCESSO = 1,
    CRIAR_FALHA = -1,
    DELETAR_SUCESSO = 2,
    DELETAR_FALHA = -2,
    OPERACOES_REALIZADAS = 3
} codigos;

// 
typedef struct listaArquivo
{
    char nomeArquivo;
    int nPrimeiroBloco;
    int nBlocosOcupados;
    int idProcesso;
    struct listaArquivo *proximo;
} ListaArquivo;

// 
typedef struct listaOperacao
{
    int idProcesso;
    int codigoOperacao;
    char nomeArquivo;
    int nBlocosCriar;
    int estado;
    struct listaOperacao *proxima;
} ListaOperacao;

// 
typedef struct disco
{
    int nBlocos;
    int nSegmentosOcupados;
    ListaArquivo *arquivos;
    ListaOperacao *operacoes;
    ListaOperacao *realizadas;
    
} Disco;

// 
Disco* montarDisco(char *);
void desmontarDisco(Disco *);
void imprimirDisco(Disco *);
int realizarOperacao(Disco *, int, int);
int realizarOperacoes(Disco *, int, int);
int criarArquivo(Disco *, char, int, int);
int deletarArquivo(Disco *, char, int, int);
void imprimirBlocos(Disco *);

// 
ListaArquivo* criarListaArquivo();
ListaArquivo* inserirListaArquivo(ListaArquivo *, char, int, int, int);
int vazioListaArquivo(ListaArquivo *);
void desalocarListaArquivo(ListaArquivo *);
void imprimirListaArquivo(ListaArquivo *);

// 
ListaOperacao* criarListaOperacao(); 
ListaOperacao* inserirListaOperacao(ListaOperacao *, int, int, char, int, int);
int vazioListaOperacao(ListaOperacao *);
void desalocarListaOperacao(ListaOperacao *);
void imprimirListaOperacao(ListaOperacao *);

