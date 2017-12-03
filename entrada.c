#include "entrada.h"
#include <iostream>
#include <vector>

using namespace std;

/*
int main(int argc, char *argv[])
{
    Disco *disco = montarDisco(argv[1]);

    imprimirDisco(disco);
    printf("\n");
    imprimirBlocos(disco);
    printf("\t%d)",realizarOperacao(disco, 1, 0));    imprimirBlocos(disco);
    printf("\t%d)",realizarOperacao(disco, 1, 0));    imprimirBlocos(disco);
    printf("\t%d)",realizarOperacao(disco, 0, 0));    imprimirBlocos(disco);
    printf("\%d)",realizarOperacao(disco, 1, 0));    imprimirBlocos(disco);
    relatorioOperacoes(disco);
    printf("\n");
    imprimirDisco(disco);
    desmontarDisco(disco);

    return 0;
}
*/

// 
vector<Processo> lerProcessos(char *entrada)
{
    // Variaveis utilizadas
    FILE *fp = fopen(entrada,"r");
    if(fp == NULL)
    {
        printf("Erro ao abrir arquivo '%s'.\n",entrada);
        return vector<Processo>();
    }
    Processo auxProcesso;
    vector<Processo> processos;
    int nRead = 0, auxInt1 = -1, auxInt2 = 0;
    char buffer[40] = {0};
    char *pch;

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
            // Obtendo 
            pch = strtok(buffer," ");
            pch[strlen(pch)-1] = '\0';
            auxProcesso.tempoInicializacao = atoi(pch);
            // Obtendo 
            pch = strtok(buffer," ");
            pch[strlen(pch)-1] = '\0';
            auxProcesso.prioridade = atoi(pch);
            // Obtendo 
            pch = strtok(buffer," ");
            pch[strlen(pch)-1] = '\0';
            auxProcesso.tempoProcessador = atoi(pch);
            // Obtendo 
            pch = strtok(buffer," ");
            pch[strlen(pch)-1] = '\0';
            auxProcesso.nBlocosMemoria = atoi(pch);
            // Obtendo 
            pch = strtok(buffer," ");
            pch[strlen(pch)-1] = '\0';
            auxProcesso.nCodigoImpressora = atoi(pch);
            // Obtendo 
            pch = strtok(buffer," ");
            pch[strlen(pch)-1] = '\0';
            auxProcesso.requisicaoScanner = atoi(pch);
            // Obtendo 
            pch = strtok(buffer," ");
            pch[strlen(pch)-1] = '\0';
            auxProcesso.requisicaoModem = atoi(pch);
            // Obtendo 
            pch = strtok(buffer," ");
            pch[strlen(pch)-1] = '\0';
            auxProcesso.nCodigoDisco = atoi(pch);
            // 
            processos.push_back(auxProcesso);
        }
    }
    // Finalizando leitura do arquivo de entrada
    fclose(fp);
    return processos;
}
