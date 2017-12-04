#include "../include/arquivos.h"
#include "../include/processos.h"

// Principal
int main(int argc,char *argv[])
{
    // Verifica argumentos
    if(argc != 3)
    {
        printf("Uso: ./sistemaArquivos.out <processes.txt> <files.txt>\n");
        exit(0);
    }
    // Inicializa estruturas
    ListaProcesso *processos = montarListaProcesso(argv[1]);
    Disco *disco = montarDisco(argv[2]);
    
    // Variável auxliar
    ListaProcesso *auxListaProcesso = NULL;
    
    // 
    printf("\n**********************\n"
             "* Lista de Processos *\n"
             "**********************\n");
    imprimirListaProcesso(processos);
    
    // 
    printf("\n*****************\n"
             "* Disco Inicial *\n"
             "*****************\n");
    imprimirDisco(disco);
    
    // 
    printf("\n*************************************\n"
             "* Mapa de Ocupacao do Disco Inicial *\n"
             "*************************************\n");
    imprimirBlocos(disco);
    
    // 
    printf("\nRealizando Operacoes...\n"
             "<Codigo de Retorno>)\n<Novo Mapa de Ocupacao do Disco>\n\n");
    
    for(auxListaProcesso = processos; auxListaProcesso != NULL; auxListaProcesso = auxListaProcesso->proximo)
    {
        printf("%d)\n",realizarOperacao(disco,auxListaProcesso->idProcesso,auxListaProcesso->prioridade));
        imprimirBlocos(disco);
        printf("\n");
    }
    
    // 
    printf("\nOperacoes Encerradas!\n");
    printf("\n###############\n"
             "# Disco Final #\n"
             "###############\n");
    imprimirDisco(disco);
    printf("\n##########################\n"
             "# Relatorio de Operacoes #\n"
             "##########################\n");
    relatorioOperacoes(disco);
    printf("\n");
    desmontarDisco(disco);

    return 0;
}


