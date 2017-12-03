#include <string>
#include <sstream>
#include <iostream>
#include <stdbool.h>
#include "../include/dispatcher.h"

using namespace std;

int main(int argc,char *argv[])
{
    if(argc != 3)
    {
        cout << "Uso: ./pseudoSO.out <processes.txt> <files.txt>" << endl;
        exit(0);
    }
    vector <Processo*> processos = montarVetorProcessos(argv[1]);
    Disco *disco = montarDisco(argv[2]);
    Dispatcher dispatcher(processos, disco);

    dispatcher.executa();

    return 0;
}
