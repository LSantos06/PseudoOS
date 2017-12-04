#ifndef DISPATCHER_H
#define DISPATCHER_H

#include "processos.h"
#include "filas.h"
#include "arquivos.h"
#include "memoria.h"
#include <algorithm>    //Para permitir o sort

using namespace std;

//Primeiro processo criado na execucao; Processo principal;
//Deve ser o responsavel pela criacao de qualquer processo
class Dispatcher{
  private:
    //Dispatcher ira conter um array com todos os processos
    //ainda a serem inicializados (colocados na fila de prontos),
    //de acordo com suas propriedades
    vector< Processo* > proximosProcessos;
    Disco *disco;

    //Determinacao do quantum do SO (1s)
    const int quantum = 1;
    //Tempo atual de execucao
    int tempo_atual;

    //Simulação de execucao de um processo na CPU
    void rodaCPU(Processo* processo);

  public:
    //Construtor
    Dispatcher(vector< Processo* > processosArquivo, Disco *discoArquivo);

    //Execucao do SO
    void executa();

};

#endif
