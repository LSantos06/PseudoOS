#ifndef QUEUE_H
#define QUEUE_H

#include <string>
#include <queue>
#include "processos.h"

using namespace std;

class FilasUsuario{
  private:
    const int n_filas = 4;

  public:
    //Vetor com as 3 filas de processo usario
    queue<Processo*> filas[3];

    //Construtor n inicializa nd
    FilasUsuario(){}

    //Insere um processo usuario pela primeira vez
    //Insercao de acordo com a prioridade
    void insere(Processo* processo);

    //Coloca um processo usuario que estava em execucao;
    //A cada vez que ocupa a CPU, a ordem de prioridade do
    //processo diminui
    void realimenta(Processo* processo);

    //Pega um processo para ir pra CPU
    Processo* escolhe_processo();

    //Retorna true se todas as filas estao vazias
    bool estaoVazias();

};

class FilaGlobal{
  private:
    const int max_processos = 1000;
    int num_processos;

  public:
    queue<Processo*> filaTempoReal;
    FilasUsuario filasUsuario;

    //Construtor sem parametros
    FilaGlobal(){
      num_processos = 0;
    }

    int getTamanho();

    //Verifica se todas as filas estao vazias
    bool estaoVazias();

    //Verifica se fila global esta cheia
    bool estaCheia();

    //Insere um processo pela primeira vez
    void insere(Processo* processo);

    //Realimentacao (estatica para tempo real, dinamica
    //para processos usuario)
    void realimenta(Processo* processo);

    //Escolha de processo de acordo com a prioridade
    Processo* escolhe_processo();
};

#endif
