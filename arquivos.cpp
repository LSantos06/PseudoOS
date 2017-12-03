#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivos.h"
#include "listaArquivosOperacoes.c"

// Main: realizando cada operacao de um processo separadamente (realizarOperacoes) -> argv[1] = "file.txt"
/*int main(int argc, char *argv[])
{
    Disco *disco = montarDisco(argv[1]);

    imprimirDisco(disco);
    printf("\n");
    printf("%d) ",realizarOperacao(disco, 1, 0));    imprimirBlocos(disco);
    printf("%d) ",realizarOperacao(disco, 1, 0));    imprimirBlocos(disco);
    printf("%d) ",realizarOperacao(disco, 0, 0));    imprimirBlocos(disco);
    printf("%d) ",realizarOperacao(disco, 1, 0));    imprimirBlocos(disco);
    printf("\n");
    imprimirDisco(disco);
    printf("\n");
    desmontarDisco(disco);

    return 0;
}*/

// Main: realizando todas operacoes de um processo de uma vez (realizarOperacoes) -> argv[1] = "file.txt"
int main(int argc, char *argv[])
{
    Disco *disco = montarDisco(argv[1]);

    imprimirDisco(disco);
    printf("\n");
    printf("%d) ",realizarOperacoes(disco, 1, 0));    imprimirBlocos(disco);
    printf("%d) ",realizarOperacoes(disco, 0, 0));    imprimirBlocos(disco);
    printf("\n");
    imprimirDisco(disco);
    printf("\n");
    desmontarDisco(disco);

    return 0;
}

// Funções de Disco

// Inicializa o disco a partir de um arquivo de entrada com nome especificado em entrada
Disco* montarDisco(char *entrada)
{
    // Variáveis utilizadas
    FILE *fp = fopen(entrada,"r");
    if(fp == NULL)
    {
        printf("Erro ao abrir arquivo '%s'.\n",entrada);
        return NULL;
    }
    Disco *disco = (Disco *)malloc(sizeof(Disco));
    ListaArquivo auxListaArquivo;
    ListaOperacao auxListaOperacao;
    int nRead = 0, auxInt1 = -1, auxInt2 = 0;
    char buffer[40] = {0};
    char *pch;

    // Preparando disco para receber conteúdo
    disco->nBlocos = -1;
    disco->nSegmentosOcupados = -1;
    disco->arquivos = criarListaArquivo();
    disco->operacoes = criarListaOperacao();
    disco->realizadas = criarListaOperacao();

    // Lendo arquivo de entrada
    while(!feof(fp))
    {
        // Obtendo linha do arquivo
        do
        {
            auxInt1++;
            nRead = fread(&buffer[auxInt1],sizeof(char),1,fp);
        }
        while(buffer[auxInt1] != '\n' && nRead != 0);
        buffer[auxInt1] = '\0';
        auxInt1 = -1;
        // Filtrando linhas vazias
        if(!feof(fp))
        {
            // Obtendo primeira linha - numero de blocos no disco
            if(disco->nBlocos == -1)
                disco->nBlocos = atoi(buffer);
            // Obtendo segunda linha - numero de segmentos ocupados
            else if(disco->nSegmentosOcupados == -1)
                disco->nSegmentosOcupados = atoi(buffer);
            // Obtendo terceira linha até linha (nSegmentosOcupados + 2) - arquivos presentes na inicialização
            else if(auxInt2 < disco->nSegmentosOcupados)
            {
                auxInt2++;
                // Obtendo nome do arquivo
                pch = strtok(buffer," ");
                auxListaArquivo.nomeArquivo = *pch;
                // Obtendo numero do primeiro bloco
                pch = strtok(NULL," ");
                pch[strlen(pch)-1] = '\0';
                auxListaArquivo.nPrimeiroBloco = atoi(pch);
                // Obtendo numero de blococs ocupados
                pch = strtok(NULL,"\n");
                auxListaArquivo.nBlocosOcupados = atoi(pch);
                // Criando nova entrada na lista/tabela de arquivos 
                disco->arquivos = inserirListaArquivo(disco->arquivos,auxListaArquivo.nomeArquivo,auxListaArquivo.nPrimeiroBloco,auxListaArquivo.nBlocosOcupados,-1);
            }
            // Obtendo linha (nSegmentosOcupados + 3_ em diante - operacoes a serem realizadas por cada processo
            else
            {
                // Obtendo id do processo responsavel pela operacao
                pch = strtok(buffer," ");
                pch[strlen(pch)-1] = '\0';
                auxListaOperacao.idProcesso = atoi(pch);
                // Obtendo codigo da operacao
                pch = strtok(NULL," ");
                pch[strlen(pch)-1] = '\0';
                auxListaOperacao.codigoOperacao = atoi(pch);
                // Caso se trate de uma operacao de deletar, obtem o nome do arquivo e zera o numero de blocos a serem criados
                if(auxListaOperacao.codigoOperacao)
                {
                    pch = strtok(NULL,"\n");
                    auxListaOperacao.nomeArquivo = *pch;
                    auxListaOperacao.nBlocosCriar = 0;
                }
                // Caso se trate de uma operacao de criar, obtem o nome do arquivo e o numero de blocos a serem criados
                else
                {
                    pch = strtok(NULL," ");
                    auxListaOperacao.nomeArquivo = *pch;
                    pch = strtok(NULL,"\n");
                    auxListaOperacao.nBlocosCriar = atoi(pch);
                }
                // Criando nova entrada na lista/tabela de operacoes
                disco->operacoes = inserirListaOperacao(disco->operacoes,auxListaOperacao.idProcesso,auxListaOperacao.codigoOperacao,auxListaOperacao.nomeArquivo,auxListaOperacao.nBlocosCriar, 0);
            }
        }
    }
    // Finalizando leitura do arquivo de entrada
    fclose(fp);
    return disco;
}

// Desaloca dados relativos ao disco, imprimindo um relatorio das operacoes realizadas (ou nao realizadas)
void desmontarDisco(Disco *disco)
{
    // Variável utilizada
    ListaOperacao *auxListaOperacao = NULL;

    desalocarListaArquivo(disco->arquivos);
    // Operacoes que foram realizadas
    for(auxListaOperacao=disco->realizadas; auxListaOperacao != NULL; auxListaOperacao = auxListaOperacao->proxima)
    {
        switch(auxListaOperacao->estado)
        {
            case CRIAR_SUCESSO:
                printf("O processo %d criou o arquivo %c.\n", auxListaOperacao->idProcesso, auxListaOperacao->nomeArquivo);
                break;
            case CRIAR_FALHA:
                printf("O processo %d nao pode criar o arquivo %c.\n", auxListaOperacao->idProcesso, auxListaOperacao->nomeArquivo);
                break;
            case DELETAR_SUCESSO:
                printf("O processo %d deletou o arquivo %c.\n", auxListaOperacao->idProcesso, auxListaOperacao->nomeArquivo);
                break;
            case DELETAR_FALHA:
                printf("O processo %d nao pode deletar o arquivo %c.\n", auxListaOperacao->idProcesso, auxListaOperacao->nomeArquivo);
                break;
            default:
                break;
        }
    }
    desalocarListaOperacao(disco->realizadas);
    // Operacoes que não foram realizadas
    for(auxListaOperacao=disco->operacoes; auxListaOperacao != NULL; auxListaOperacao = auxListaOperacao->proxima)
    {
        printf("O processo %d nao foi executado.\n", auxListaOperacao->idProcesso);
    }
    desalocarListaOperacao(disco->operacoes);
    free(disco);
    return;
}

// Imprime informações do disco
void imprimirDisco(Disco *disco)
{
    printf("nBlocos: %d\nnSegmentosOcupados: %d\n",disco->nBlocos,disco->nSegmentosOcupados);
    printf("arquivos:\n");
    imprimirListaArquivo(disco->arquivos);
    printf("operacoes:\n");
    imprimirListaOperacao(disco->operacoes);
    printf("realizadas:\n");
    imprimirListaOperacao(disco->realizadas);
    return;
}

// Executa uma operacao do sistema de arquivos
int realizarOperacao(Disco *disco, int idProcesso, int prioridadeProcesso)
{
    // Variaveis utilizadas
    ListaOperacao *auxListaOperacao = NULL, *antListaOperacao = NULL;
    int auxInt = 0;

    // Percorre lista de operacoes
    for(auxListaOperacao = disco->operacoes; auxListaOperacao != NULL; auxListaOperacao = auxListaOperacao->proxima)
    {
        // Verifica se operacao é do processo requisitando acesso ao sistema de arquivos
        if(auxListaOperacao->idProcesso == idProcesso)
        {
            // Retira operação da lista de operacoes
            if(antListaOperacao != NULL)
                antListaOperacao->proxima = auxListaOperacao->proxima;
            else
                disco->operacoes = auxListaOperacao->proxima;
            // Executa  a operacao de acordo com seu tipo (criar ou deletar)
            if(auxListaOperacao->codigoOperacao == 0)
                auxInt = criarArquivo(disco,auxListaOperacao->nomeArquivo,auxListaOperacao->nBlocosCriar,idProcesso);
            else
                auxInt = deletarArquivo(disco,auxListaOperacao->nomeArquivo,idProcesso,prioridadeProcesso);
            // Insere a operacao na lista de operacoes já realizadas
            disco->realizadas = inserirListaOperacao(disco->realizadas,auxListaOperacao->idProcesso,auxListaOperacao->codigoOperacao,auxListaOperacao->nomeArquivo,auxListaOperacao->nBlocosCriar,auxInt);
            // Libera espaço ocupado anteriormente e retorna o codigo resultante da operacao
            free(auxListaOperacao);
            return auxInt;
        }
        antListaOperacao = auxListaOperacao;
    }
    // Caso não encontre operação relativa ao processo requisitante
    return OPERACAO_NAO_REALIZADA;
}

// Executa todas as operacoes de um processo no sistema de arquivos
int realizarOperacoes(Disco *disco, int idProcesso, int prioridadeProcesso)
{
    // Variaveis utilizadas
    ListaOperacao *auxListaOperacao = NULL, *antListaOperacao = NULL;
    ListaOperacao aux2ListaOperacao =
    {
        .idProcesso = 0,
        .codigoOperacao = 0,
        .nomeArquivo = (char)0,
        .nBlocosCriar = 0,
        .estado = 0,
        .proxima = NULL
    };
    int auxInt = 0;

    // Percorre lista de operacoes
    for(auxListaOperacao = disco->operacoes; auxListaOperacao != NULL; auxListaOperacao = auxListaOperacao->proxima)
    {
        // Verifica se operacao é do processo requisitando acesso ao sistema de arquivos
        if(auxListaOperacao->idProcesso == idProcesso)
        {
            // Retira operação da lista de operacoes
            if(antListaOperacao != NULL)
                antListaOperacao->proxima = auxListaOperacao->proxima;
            else
                disco->operacoes = auxListaOperacao->proxima;
            // Executa  a operacao de acordo com seu tipo (criar ou deletar)
            if(auxListaOperacao->codigoOperacao == 0)
                auxInt = criarArquivo(disco,auxListaOperacao->nomeArquivo,auxListaOperacao->nBlocosCriar,idProcesso);
            else
                auxInt = deletarArquivo(disco,auxListaOperacao->nomeArquivo,idProcesso,prioridadeProcesso);
            // Insere a operacao na lista de operacoes já realizadas
            disco->realizadas = inserirListaOperacao(disco->realizadas,auxListaOperacao->idProcesso,auxListaOperacao->codigoOperacao,auxListaOperacao->nomeArquivo,auxListaOperacao->nBlocosCriar, auxInt);
            // Libera espaco ocupado anteriormente e continua a buscar mais operacoes
            if(antListaOperacao != NULL)
            {
                free(auxListaOperacao);
                auxListaOperacao = antListaOperacao;
            }
            else
            {
                aux2ListaOperacao.proxima = auxListaOperacao->proxima;
                free(auxListaOperacao);
                auxListaOperacao = (ListaOperacao *)&aux2ListaOperacao;
            }
        }
        else
            antListaOperacao = auxListaOperacao;
    }
    // Retorna o codigo indicado que todas operacoes do processo em questao foram realizadas
    return OPERACOES_REALIZADAS;
}

// Operacao para criacao de arquivos (First-Fit)
int criarArquivo(Disco *disco, char nomeArquivo, int nBlocosCriar, int idProcesso)
{
    // Variaveis utilizadas
    ListaArquivo *auxListaArquivo = NULL;
    ListaArquivo *novo = NULL;
    int firstFlag = 1;

    // Percorre lista/tabela de arquivos
    for(auxListaArquivo = disco->arquivos; auxListaArquivo != NULL; auxListaArquivo = auxListaArquivo->proximo)
    {
        // Criando novo arquivo nos blocos livres inicias do disco
        if(firstFlag)
        {
            firstFlag = 0;
            if(nBlocosCriar <= auxListaArquivo->nPrimeiroBloco)
            {
                novo = (ListaArquivo *)malloc(sizeof(ListaArquivo));
                novo->nomeArquivo = nomeArquivo;
                novo->nPrimeiroBloco = 0;
                novo->nBlocosOcupados = nBlocosCriar;
                novo->idProcesso = idProcesso;
                novo->proximo = auxListaArquivo;
                disco->arquivos = novo;
                disco->nSegmentosOcupados++;
                return CRIAR_SUCESSO;
            }
        }
        // Criando novo arquivo nos blocos livres entre arquivos ja existentes
        if(auxListaArquivo->proximo != NULL && nBlocosCriar <= auxListaArquivo->proximo->nPrimeiroBloco - (auxListaArquivo->nPrimeiroBloco + auxListaArquivo->nBlocosOcupados))
        {
            novo = (ListaArquivo *)malloc(sizeof(ListaArquivo));
            novo->nomeArquivo = nomeArquivo;
            novo->nPrimeiroBloco = auxListaArquivo->nPrimeiroBloco + auxListaArquivo->nBlocosOcupados;
            novo->nBlocosOcupados = nBlocosCriar;
            novo->idProcesso = idProcesso;
            novo->proximo = auxListaArquivo->proximo;
            auxListaArquivo->proximo = novo;
            disco->nSegmentosOcupados++;
            return CRIAR_SUCESSO;
        }
        // Criando novo arquivo nos blocos livres ao final do disco
        if(auxListaArquivo->proximo == NULL && nBlocosCriar <= disco->nBlocos - (auxListaArquivo->nPrimeiroBloco + auxListaArquivo->nBlocosOcupados))
        {
            novo = (ListaArquivo *)malloc(sizeof(ListaArquivo));
            novo->nomeArquivo = nomeArquivo;
            novo->nPrimeiroBloco = auxListaArquivo->nPrimeiroBloco + auxListaArquivo->nBlocosOcupados;
            novo->nBlocosOcupados = nBlocosCriar;
            novo->idProcesso = idProcesso;
            novo->proximo = auxListaArquivo->proximo;
            auxListaArquivo->proximo = novo;
            disco->nSegmentosOcupados++;
            return CRIAR_SUCESSO;
        }
    }
    // Retornando codigo de falha dado que nao foi encontrado blocos contiguos suficientes para criar o novo arquivo
    return CRIAR_FALHA;
}

// Operacao para deletar arquivos
int deletarArquivo(Disco *disco, char nomeArquivo, int idProcesso, int prioridadeProcesso)
{
    // Variaveis utilizadas
    ListaArquivo *auxListaArquivo = NULL, *antListaArquivo = NULL;

    // Percorre lista/tabela de arquivos
    for(auxListaArquivo = disco->arquivos; auxListaArquivo != NULL; auxListaArquivo = auxListaArquivo->proximo)
    {
        // Verifica correnspondencia entre o nome do arquivo a ser deletado e o apontado por auxListaArquivo
        if(auxListaArquivo->nomeArquivo == nomeArquivo)
        {
            // Deleta arquivo caso a prioridade do processo seja 0 ou se o arquivo foi criado pelo processo requisitante
            if((!prioridadeProcesso) || (prioridadeProcesso && auxListaArquivo->idProcesso == idProcesso))
            {
                // Deleta arquivo do inicio da tabela
                if(antListaArquivo != NULL)
                    antListaArquivo->proximo = auxListaArquivo->proximo;
                // Deleta arquivo no meio ou fim da tabela
                else
                    disco->arquivos = auxListaArquivo->proximo;
                free(auxListaArquivo);  
                disco->nSegmentosOcupados--;
                return DELETAR_SUCESSO;
            }
            // Retorna codigo de falha caso o processo nao tenha permissao para deletar o processo
            else
                return DELETAR_FALHA;
        }
        antListaArquivo = auxListaArquivo;
    }
    // Retorna codigo de falha caso o arquivo a ser deletado nao exista
    return DELETAR_FALHA;
}

// Imprime mapa de ocupacao do disco
void imprimirBlocos(Disco *disco)
{
    // Variaveis utilizadas
    ListaArquivo *auxListaArquivo = NULL;
    int auxInt = 0;
    int firstFlag = 1;

    // Percorre lista/tabela de arquivos
    for(auxListaArquivo = disco->arquivos; auxListaArquivo != NULL; auxListaArquivo = auxListaArquivo->proximo)
    {
        // Imprimindo blocos livres inicias do disco
        if(firstFlag)
        {
            firstFlag = 0;
            while(auxInt < auxListaArquivo->nPrimeiroBloco)
            {
                printf("|0");
                auxInt++;
            }   
            auxInt = 0;
        }
        // Imprimindo blocos ocupados pelo arquivo apontando por auxListaArquivo
        while(auxInt < auxListaArquivo->nBlocosOcupados)
        {
            printf("|%c",auxListaArquivo->nomeArquivo);
            auxInt++;
        }
        auxInt = 0;
        // Imprimindo blocos livres entre arquivos existentes
        if(!vazioListaArquivo(auxListaArquivo->proximo))
        {
            while(auxInt < auxListaArquivo->proximo->nPrimeiroBloco - (auxListaArquivo->nPrimeiroBloco + auxListaArquivo->nBlocosOcupados))
            {
                printf("|0");
                auxInt++;
            }
        }
        // Imprimindo blocos livres ao final do disco
        else
        {
            while(auxInt < disco->nBlocos - (auxListaArquivo->nPrimeiroBloco + auxListaArquivo->nBlocosOcupados))
            {
                printf("|0");
                auxInt++;
            }
            printf("|\n");
        }
        auxInt = 0;
    }
    return;
}

