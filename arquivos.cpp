#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"arquivos.h"

// 
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

// 
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

// 

// 
Disco* montarDisco(char *entrada)
{
    // 
    FILE *fp = fopen(entrada,"r");
    if(fp == NULL)
    {
        printf("Erro ao abrir arquivo '%s'.\n",entrada);
        return NULL;
    }
    Disco *disco = (Disco *)malloc(sizeof(Disco));
    ListaArquivo auxListaArquivo;
    int nRead = 0, auxInt1 = -1, auxInt2 = 0;
    ListaOperacao auxListaOperacao;
    char buffer[40] = {0};
    char *pch;

    // 
    disco->nBlocos = -1;
    disco->nSegmentosOcupados = -1;
    disco->arquivos = criarListaArquivo();
    disco->operacoes = criarListaOperacao();
    disco->realizadas = criarListaOperacao();

    // 
    while(!feof(fp))
    {
        // 
        do
        {
            auxInt1++;
            nRead = fread(&buffer[auxInt1],sizeof(char),1,fp);
        }
        while(buffer[auxInt1] != '\n' && nRead != 0);
        buffer[auxInt1] = '\0';
        auxInt1 = -1;
        // 
        if(!feof(fp))
        {
            // 
            if(disco->nBlocos == -1)
                disco->nBlocos = atoi(buffer);
            // 
            else if(disco->nSegmentosOcupados == -1)
                disco->nSegmentosOcupados = atoi(buffer);
            // 
            else if(auxInt2 < disco->nSegmentosOcupados)
            {
                auxInt2++;
                // 
                pch = strtok(buffer," ");
                auxListaArquivo.nomeArquivo = *pch;
                // 
                pch = strtok(NULL," ");
                pch[strlen(pch)-1] = '\0';
                auxListaArquivo.nPrimeiroBloco = atoi(pch);
                // 
                pch = strtok(NULL,"\n");
                auxListaArquivo.nBlocosOcupados = atoi(pch);
                // 
                disco->arquivos = inserirListaArquivo(disco->arquivos,auxListaArquivo.nomeArquivo,auxListaArquivo.nPrimeiroBloco,auxListaArquivo.nBlocosOcupados,-1);
            }
            // 
            else
            {
                // 
                pch = strtok(buffer," ");
                pch[strlen(pch)-1] = '\0';
                auxListaOperacao.idProcesso = atoi(pch);
                // 
                pch = strtok(NULL," ");
                pch[strlen(pch)-1] = '\0';
                auxListaOperacao.codigoOperacao = atoi(pch);
                // 
                if(auxListaOperacao.codigoOperacao)
                {
                    pch = strtok(NULL,"\n");
                    auxListaOperacao.nomeArquivo = *pch;
                    auxListaOperacao.nBlocosCriar = 0;
                }
                // 
                else
                {
                    // 
                    pch = strtok(NULL," ");
                    auxListaOperacao.nomeArquivo = *pch;
                    // 
                    pch = strtok(NULL,"\n");
                    auxListaOperacao.nBlocosCriar = atoi(pch);
                }
                // 
                disco->operacoes = inserirListaOperacao(disco->operacoes,auxListaOperacao.idProcesso,auxListaOperacao.codigoOperacao,auxListaOperacao.nomeArquivo,auxListaOperacao.nBlocosCriar, 0);
            }
        }
    }
    fclose(fp);
    return disco;
}

// 
void desmontarDisco(Disco *disco)
{
    ListaOperacao *auxListaOperacao = NULL;

    desalocarListaArquivo(disco->arquivos);
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
    for(auxListaOperacao=disco->operacoes; auxListaOperacao != NULL; auxListaOperacao = auxListaOperacao->proxima)
    {
        printf("O processo %d nao foi executado.\n", auxListaOperacao->idProcesso);
    }
    desalocarListaOperacao(disco->operacoes);
    free(disco);
    return;
}

// 
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

// 

// 
int realizarOperacao(Disco *disco, int idProcesso, int prioridadeProcesso)
{
    ListaOperacao *auxListaOperacao = NULL, *antListaOperacao = NULL;
    int auxInt = 0;

    for(auxListaOperacao = disco->operacoes; auxListaOperacao != NULL; auxListaOperacao = auxListaOperacao->proxima)
    {
        if(auxListaOperacao->idProcesso == idProcesso)
        {
            // 
            if(antListaOperacao != NULL)
                antListaOperacao->proxima = auxListaOperacao->proxima;
            else
                disco->operacoes = auxListaOperacao->proxima;
            // 
            if(auxListaOperacao->codigoOperacao == 0)
                auxInt = criarArquivo(disco,auxListaOperacao->nomeArquivo,auxListaOperacao->nBlocosCriar,idProcesso);
            else
                auxInt = deletarArquivo(disco,auxListaOperacao->nomeArquivo,idProcesso,prioridadeProcesso);
            // 
            disco->realizadas = inserirListaOperacao(disco->realizadas,auxListaOperacao->idProcesso,auxListaOperacao->codigoOperacao,auxListaOperacao->nomeArquivo,auxListaOperacao->nBlocosCriar,auxInt);
            free(auxListaOperacao);
            return auxInt;
        }
        antListaOperacao = auxListaOperacao;
    }
    return OPERACAO_NAO_REALIZADA;
}

// 
int realizarOperacoes(Disco *disco, int idProcesso, int prioridadeProcesso)
{
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

    for(auxListaOperacao = disco->operacoes; auxListaOperacao != NULL; auxListaOperacao = auxListaOperacao->proxima)
    {
        if(auxListaOperacao->idProcesso == idProcesso)
        {
            // 
            if(antListaOperacao != NULL)
                antListaOperacao->proxima = auxListaOperacao->proxima;
            else
                disco->operacoes = auxListaOperacao->proxima;
            // 
            if(auxListaOperacao->codigoOperacao == 0)
                auxInt = criarArquivo(disco,auxListaOperacao->nomeArquivo,auxListaOperacao->nBlocosCriar,idProcesso);
            else
                auxInt = deletarArquivo(disco,auxListaOperacao->nomeArquivo,idProcesso,prioridadeProcesso);
            // 
            disco->realizadas = inserirListaOperacao(disco->realizadas,auxListaOperacao->idProcesso,auxListaOperacao->codigoOperacao,auxListaOperacao->nomeArquivo,auxListaOperacao->nBlocosCriar, auxInt);
            // 
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
    return OPERACOES_REALIZADAS;
}

// 
int criarArquivo(Disco *disco, char nomeArquivo, int nBlocosCriar, int idProcesso)
{
    ListaArquivo *auxListaArquivo = NULL;
    ListaArquivo *novo = NULL;
    int firstFlag = 1;

    for(auxListaArquivo = disco->arquivos; auxListaArquivo != NULL; auxListaArquivo = auxListaArquivo->proximo)
    {
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
        if(vazioListaArquivo(auxListaArquivo->proximo) && nBlocosCriar <= disco->nBlocos - (auxListaArquivo->nPrimeiroBloco + auxListaArquivo->nBlocosOcupados))
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
    return CRIAR_FALHA;
}

// 
int deletarArquivo(Disco *disco, char nomeArquivo, int idProcesso, int prioridadeProcesso)
{
    ListaArquivo *auxListaArquivo = NULL, *antListaArquivo = NULL;

    for(auxListaArquivo = disco->arquivos; auxListaArquivo != NULL; auxListaArquivo = auxListaArquivo->proximo)
    {
        if(auxListaArquivo->nomeArquivo == nomeArquivo)
        {
            if((!prioridadeProcesso) || (prioridadeProcesso && auxListaArquivo->idProcesso == idProcesso))
            {
                if(antListaArquivo != NULL)
                    antListaArquivo->proximo = auxListaArquivo->proximo;
                else
                    disco->arquivos = auxListaArquivo->proximo;
                free(auxListaArquivo);  
                disco->nSegmentosOcupados--;
                return DELETAR_SUCESSO;
            }
            else
                return DELETAR_FALHA;
        }
        antListaArquivo = auxListaArquivo;
    }
    return DELETAR_FALHA;
}

// 
void imprimirBlocos(Disco *disco)
{
    ListaArquivo *auxListaArquivo = NULL;
    int auxInt = 0;
    int firstFlag = 1;
    
    for(auxListaArquivo = disco->arquivos; auxListaArquivo != NULL; auxListaArquivo = auxListaArquivo->proximo)
    {
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
        while(auxInt < auxListaArquivo->nBlocosOcupados)
        {
            printf("|%c",auxListaArquivo->nomeArquivo);
            auxInt++;
        }
        auxInt = 0;
        if(!vazioListaArquivo(auxListaArquivo->proximo))
        {
            while(auxInt < auxListaArquivo->proximo->nPrimeiroBloco - (auxListaArquivo->nPrimeiroBloco + auxListaArquivo->nBlocosOcupados))
            {
                printf("|0");
                auxInt++;
            }
        }
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

// 

// 
ListaArquivo* criarListaArquivo()
{
    return NULL;
}

// 
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

// 
int vazioListaArquivo(ListaArquivo *arquivos)
{
    if(arquivos == NULL)
        return 1;
    else
        return 0;
}

// 
void desalocarListaArquivo(ListaArquivo *arquivos)
{
    if(!vazioListaArquivo(arquivos))
    {
        desalocarListaArquivo(arquivos->proximo);
        free(arquivos);
    }
    return;
}

// 
void imprimirListaArquivo(ListaArquivo *arquivos)
{
    if(!vazioListaArquivo(arquivos))
    {
        printf("nomeArquivo: %c | nPrimeiroBloco: %d | nBlocosOcupados: %d | idProcesso: %d\n",arquivos->nomeArquivo,arquivos->nPrimeiroBloco,arquivos->nBlocosOcupados,arquivos->idProcesso);
        imprimirListaArquivo(arquivos->proximo);
    }
    return;
}

// 

// 
ListaOperacao* criarListaOperacao()
{
    return NULL;
}

// 
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

// 
int vazioListaOperacao(ListaOperacao *operacoes)
{
    if(operacoes == NULL)
        return 1;
    else
        return 0;
}

// 
void desalocarListaOperacao(ListaOperacao *operacoes)
{
    if(!vazioListaOperacao(operacoes))
    {
        desalocarListaOperacao(operacoes->proxima);
        free(operacoes);
    }
    return;
}

// 
void imprimirListaOperacao(ListaOperacao *operacoes)
{
    if(!vazioListaOperacao(operacoes))
    {
        printf("idProcesso: %d | codigoOperacao: %d | nomeArquivo: %c | nBlocosCriar: %d | estado: %d\n",operacoes->idProcesso,operacoes->codigoOperacao,operacoes->nomeArquivo,operacoes->nBlocosCriar,operacoes->estado);
        imprimirListaOperacao(operacoes->proxima);
    }
    return;
}
