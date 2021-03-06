#include "../include/processos.h"

/////////////////////////
// Funções de Processo //
/////////////////////////

// Inicializa o vetor de processos a partir de um arquivo de entrada com nome especificado em entrada
ListaProcesso* montarListaProcesso(char *entrada)
{
    // Variaveis utilizadas
    FILE *fp = fopen(entrada,"r");
    if(fp == NULL)
    {
        printf("Erro ao abrir arquivo '%s'.\n",entrada);
        exit(1);
    }
    ListaProcesso processo;
    ListaProcesso *processos = criarListaProcesso();
    int nRead = 0, auxInt1 = -1, auxInt2 = 0;
    char buffer[100] = {0};
    char *pch = NULL;

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
        if(buffer[0] != '\0' && !feof(fp))
        {
            // Definindo um ID para o processo
            processo.idProcesso = auxInt2;
            // Obtendo tempo de inicializacao
            pch = strtok(buffer," ");
            pch[strlen(pch)-1] = '\0';
            processo.tempoInicializacao = atoi(pch);
            // Obtendo prioridade
            pch = strtok(NULL," ");
            pch[strlen(pch)-1] = '\0';
            processo.prioridade = atoi(pch);
            // Obtendo tempo de processador
            pch = strtok(NULL," ");
            pch[strlen(pch)-1] = '\0';
            processo.tempoProcessador = atoi(pch);
            // Obtendo blocos em memoria
            pch = strtok(NULL," ");
            pch[strlen(pch)-1] = '\0';
            processo.blocosMemoria = atoi(pch);
            // Obtendo numero codigo da impressora requisitada
            pch = strtok(NULL," ");
            pch[strlen(pch)-1] = '\0';
            processo.nCodigoImpressora = atoi(pch);
            // Obtendo requisicao do scanner
            pch = strtok(NULL," ");
            pch[strlen(pch)-1] = '\0';
            processo.requisicaoScanner = atoi(pch);
            // Obtendo requisicao do modem
            pch = strtok(NULL," ");
            pch[strlen(pch)-1] = '\0';
            processo.requisicaoModem = atoi(pch);
            // Obtendo numero codigo do disco
            pch = strtok(NULL,"\0");
            processo.nCodigoDisco = atoi(pch);
            // Criando novo processo no vetor de processos
            processos = inserirListaProcesso(processos, processo.idProcesso, processo.tempoInicializacao, processo.prioridade, processo.tempoProcessador, processo.blocosMemoria, processo.nCodigoImpressora, processo.requisicaoScanner, processo.requisicaoModem, processo.nCodigoDisco);
            // Incrementando contador auxiliar de ID
            auxInt2++;
        }
    }
    // Finalizando leitura do arquivo de entrada
    fclose(fp);
    return processos;
}

//////////////////////////////////////////
// Funcoes de lista/tabela de processos //
//////////////////////////////////////////

// Cria lista/tabela
ListaProcesso* criarListaProcesso()
{
    return NULL;
}

// Insere novo elemento ao final da lista/tabela
ListaProcesso* inserirListaProcesso(ListaProcesso *processos, int idProcesso, int tempoInicializacao, int prioridade, int tempoProcessador, int blocosMemoria, int nCodigoImpressora, int requisicaoScanner, int requisicaoModem, int nCodigoDisco)
{
	ListaProcesso *auxListaProcesso = NULL;
	ListaProcesso *novo = (ListaProcesso *)malloc(sizeof(ListaProcesso));

    novo->idProcesso = idProcesso;
    novo->tempoInicializacao = tempoInicializacao;
    novo->prioridade = prioridade;
    novo->tempoProcessador = tempoProcessador;
    novo->blocosMemoria = blocosMemoria;
    novo->nCodigoImpressora = nCodigoImpressora;
    novo->requisicaoScanner = requisicaoScanner ;
    novo->requisicaoModem = requisicaoModem;
    novo->nCodigoDisco = nCodigoDisco;
    novo->proximo = NULL;
    if(processos != NULL)
    {
        for(auxListaProcesso = processos; auxListaProcesso->proximo != NULL; auxListaProcesso = auxListaProcesso->proximo);
        auxListaProcesso->proximo = novo;
    }
    else
        processos = novo;
    return processos;
}

// Desaloca conteudo da lista/tabela
void desalocarListaProcesso(ListaProcesso *processos)
{
    if(processos != NULL)
    {
        desalocarListaProcesso(processos->proximo);
        free(processos);
    }
    return;
}

// Imprime elementos da lista/tabela
void imprimirListaProcesso(ListaProcesso *processos)
{
    if(processos != NULL)
    {
        printf("idProcesso: %d | tempoInicializacao: %d | prioridade: %d | tempoProcessador: %d blocosMemoria: %d | nCodigoImpressora: %d | requisicaoScanner: %d | requisicaoModem: %d | nCodigoDisco: %d\n",processos->idProcesso, processos->tempoInicializacao, processos->prioridade, processos->tempoProcessador, processos->blocosMemoria, processos->nCodigoImpressora, processos->requisicaoScanner, processos->requisicaoModem, processos->nCodigoDisco);
        imprimirListaProcesso(processos->proximo);
    }
    return;
}
