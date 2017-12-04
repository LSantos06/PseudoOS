#include "../include/arquivos.h"

// Main: realizando cada operacao de um processo separadamente (realizarOperacoes) -> argv[1] = "file.txt"
int main(int argc, char *argv[])
{
    Disco *disco = montarDisco(argv[1]);

    imprimirDisco(disco);
    printf("\n");
    imprimirBlocos(disco);
    printf("%d)\t",realizarOperacao(disco, 1, 0));    imprimirBlocos(disco);
    printf("%d)\t",realizarOperacao(disco, 1, 0));    imprimirBlocos(disco);
    printf("%d)\t",realizarOperacao(disco, 0, 0));    imprimirBlocos(disco);
    printf("%d)\t",realizarOperacao(disco, 1, 0));    imprimirBlocos(disco);
    relatorioOperacoes(disco);
    printf("\n");
    imprimirDisco(disco);
    desmontarDisco(disco);

    return 0;
}

// Main: realizando todas operacoes de um processo de uma vez (realizarOperacoes) -> argv[1] = "file.txt"
/*int main(int argc, char *argv[])
{
    Disco *disco = montarDisco(argv[1]);

    imprimirDisco(disco);
    printf("\n");
    imprimirBlocos(disco);
    printf("%d)\t",realizarOperacoes(disco, 1, 0));    imprimirBlocos(disco);
    printf("%d)\t",realizarOperacoes(disco, 0, 0));    imprimirBlocos(disco);
    relatorioOperacoes(disco);
    printf("\n");
    imprimirDisco(disco);
    desmontarDisco(disco);

    return 0;
}*/
