#include "filas.h"

//Metodos de processo usuario
void FilasUsuario::insere(Processo* processo){
  //Coloca processo na fila na posicao correta
  filas[(processo->getPrioridade())-1].push(processo);
}

void FilasUsuario::realimenta(Processo* processo){
  //Aumenta prioridade
  if(processo->getPrioridade() < n_filas - 1){
    processo->setPrioridade(processo->getPrioridade() + 1);
  }

  filas[(processo->getPrioridade())-1].push(processo);
}

Processo* FilasUsuario::escolhe_processo(){
  Processo *retorno;

  //Se fila 1 tiver com algum elemento
  if(!filas[0].empty()){
    retorno = filas[0].front();
    filas[0].pop();
    return retorno;
  }
  //Se fila 2 tiver vazia
  if(!filas[1].empty()){
    retorno = filas[1].front();
    filas[1].pop();
    return retorno;
  }

  retorno = filas[2].front();
  filas[2].pop();
  return retorno;
}

bool FilasUsuario::estaoVazias(){
  if(filas[0].empty() && filas[1].empty() && filas[2].empty()){
    return true;
  }
  return false;
}

int FilaGlobal::getTamanho(){
  return num_processos;
}

bool FilaGlobal::eh_usuario(Processo* processo){
  //Se for 0, eh de tempo real
  if(!processo->getPrioridade()){
    return false;
  }
  return true;
}

bool FilaGlobal::estaoVazias(){
  if(filaTempoReal.empty() && filasUsuario.estaoVazias()){
    return true;
  }
  return false;
}

bool FilaGlobal::estaCheia(){
  if(num_processos == max_processos){
    return true;
  }
  return false;
}

void FilaGlobal::insere(Processo* processo){
  if(estaCheia()){
    return;
  }
  if(!eh_usuario(processo)){
    filaTempoReal.push(processo);
  }
  else{
    filasUsuario.insere(processo);
  }
  num_processos++;

}

void FilaGlobal::realimenta(Processo* processo){
  if(!eh_usuario(processo)){
    filaTempoReal.push(processo);
  }
  else{
    filasUsuario.insere(processo);
  }
}

Processo* FilaGlobal::escolhe_processo(){
  if(estaoVazias()){
    return NULL;
  }

  num_processos--;

  Processo *retorno;

  //Se fila de TR NAO estiver vazia
  if(!filaTempoReal.empty()){
    retorno = filaTempoReal.front();
    filaTempoReal.pop();
    return retorno;
  }
  else{
    return filasUsuario.escolhe_processo();
  }
}
