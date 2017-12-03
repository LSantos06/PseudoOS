#include "dispatcher.h"

//Funcao de ordenacao para o vetor de processos
bool ordena (Processo *proc1, Processo *proc2){
  return (proc1->getTempoInicializacao() < proc2->getTempoInicializacao());
}

Dispatcher::Dispatcher(vector< Processo* > processosArquivo, Disco *discoArquivo){
  tempo_atual = 0;
  //Atribui para a lista de processos do Dispatcher
  proximosProcessos = processosArquivo;
  //Atribui para a estrutura de disco do Dispatcher
  disco = discoArquivo;

  //Ordena em ordem crescente de tempo de inicializacao
  sort(proximosProcessos.begin(), proximosProcessos.end(), ordena);
}

void Dispatcher::rodaCPU(Processo* processo){
  //Diminui tempo do processo em 1 quantum (simula execucao)
  processo->setTempoProcessador(processo->getTempoProcessador() - 1);

  /************** Acoes a serem simuladas na operacao *********/
  //Operacoes de um processo no sistema de arquivos
  realizarOperacoes(disco, processo->getID(),processo->getPrioridade());

}

void Dispatcher::executa(){
  FilaGlobal filaGlobal;

  Processo *processoAtual = nullptr;

  //Enquanto houver processos para executar
  while(!filaGlobal.estaoVazias() || !proximosProcessos.empty()){
    //Enquanto o tempo atual for igual ao tempo de inicializacao
    //dos proximos processos a serem inseridos, insere na fila global
    while(!proximosProcessos.empty() &&
    proximosProcessos.front()->getTempoInicializacao() == tempo_atual){
      cout << "dispatcher =>" << endl;
      proximosProcessos.front()->print();
      //Insere elemento na fila
      filaGlobal.insere(proximosProcessos.front());
      //Apaga primeiro elemento
      proximosProcessos.erase(proximosProcessos.begin());
    }

    //Com elementos devidamente inseridos na fila de prontos,
    //pode-se escolher 1 da fila global
    if(!processoAtual && !filaGlobal.estaoVazias()){
      processoAtual = filaGlobal.escolhe_processo();
    }

    //Se processo nao for null
    if(processoAtual){
      //Manda pra CPU
      rodaCPU(processoAtual);
      if(processoAtual->getTempoProcessador() <= 0){
        //TODO: Operacoes de desalocacao de E/S e memoria
        processoAtual = nullptr;
      }
      //Se n tiver acabado e for processo usuario, sofre preempcao
      else if(processoAtual->eh_usuario()){
        filaGlobal.realimenta(processoAtual);
        processoAtual = nullptr;
      }
    } //if processoAtual
    tempo_atual++;
  } //while houver processos

  //Apos fim da execucao, imprimir relatorio de operacoes pros processos
  relatorioOperacoes(disco);
  cout << endl << "Mapa de ocupacao do disco:" << endl;
  //Impressao dos blocos
  imprimirBlocos(disco);
}
