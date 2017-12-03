#include "processos.h"
#include <sstream>

// 0 tempo_inicializacao
// 1 prioridade
// 2 tempo_processador
// 3 blocos_memoria
// 4 numero_impressora
// 5 requisicao_scanner
// 6 requisicao_modem
// 7 numero_disco

Processo::Processo(string valores_entrada[10]){
  copy(valores_entrada,valores_entrada + 10, atributos);
}

int Processo::getTempoInicializacao(){
    //Faz uma conversao de um tipo string para int
    stringstream convert(atributos[0]);

    int retorno;

    return convert >> retorno ? retorno : 0;
}

int Processo::getPrioridade(){
  //Faz uma conversao de um tipo string para int
  stringstream convert(atributos[1]);

  int retorno;

  return convert >> retorno ? retorno : 0;
}

void Processo::setPrioridade(int prioridade){
  stringstream number2string;
  number2string << prioridade;

  atributos[1] = number2string.str();
}

int Processo::getTempoProcessador(){
  //Faz uma conversao de um tipo string para int
  stringstream convert(atributos[2]);

  int retorno;

  return convert >> retorno ? retorno : 0;
}

void Processo::setTempoProcessador(int tempo){
  stringstream number2string;
  number2string << tempo;

  atributos[2] = number2string.str();
}

int Processo::getBlocos(){
  //Faz uma conversao de um tipo string para int
  stringstream convert(atributos[3]);

  int retorno;

  return convert >> retorno ? retorno : 0;
}

void Processo::setBlocos(int blocos){
  stringstream number2string;
  number2string << blocos;

  atributos[3] = number2string.str();
}

int Processo::getImpressora(){
  //Faz uma conversao de um tipo string para int
  stringstream convert(atributos[4]);

  int retorno;

  return convert >> retorno ? retorno : 0;
}

void Processo::setImpressora(int impressora){
  stringstream number2string;
  number2string << impressora;

  atributos[4] = number2string.str();
}

bool Processo::getScanner(){
  //Compare retorna 0 se strings sao iguais
  if(atributos[5].compare("0")){
    return true;
  }

  return false;
}

void Processo::setScanner(bool scanner){
  if(scanner){
    atributos[5] = "1";
    return;
  }

  atributos[5] = "0";
}

bool Processo::getModem(){
  //Compare retorna 0 se strings sao iguais
  if(atributos[6].compare("0")){
    return true;
  }

  return false;
}

void Processo::setModem(bool modem){
  if(modem){
    atributos[6] = "1";
    return;
  }

  atributos[6] = "0";
}

int Processo::getDisco(){
  //Faz uma conversao de um tipo string para int
  stringstream convert(atributos[7]);

  int retorno;

  return convert >> retorno ? retorno : 0;
}

void Processo::setDisco(int disco){
  stringstream number2string;
  number2string << disco;

  atributos[7] = number2string.str();
}

int Processo::getID(){
  //Faz uma conversao de um tipo string para int
  stringstream convert(atributos[8]);

  int retorno;

  return convert >> retorno ? retorno : 0;
}

int Processo::getMemOffset(){
  //Faz uma conversao de um tipo string para int
  stringstream convert(atributos[9]);

  int retorno;

  return convert >> retorno ? retorno : 0;
}

void Processo::setMemOffset(int offset){
  stringstream number2string;
  number2string << offset;

  atributos[9] = number2string.str();
}

void Processo::print(){
  cout << "PID: " << getID() << endl;
  cout << "offset: " << getMemOffset() << endl;
  cout << "blocks: " << getBlocos() << endl;
  cout << "priority: " << getPrioridade() << endl;
  cout << "time: " << getTempoProcessador() << endl;
  cout << "printers: " << getImpressora() << endl;
  cout << "scanners: " << getScanner() << endl;
  cout << "modems: " << getModem() << endl;
  cout << "drives: " << getDisco() << endl;
}

bool Processo::eh_usuario(){
  //Se for 0, eh de tempo real
  if(!getPrioridade()){
    return false;
  }
  return true;
}
