#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <stdbool.h>
#include <iostream>

using namespace std;

class Processo{
    // 0 tempo_inicializacao
    // 1 prioridade
    // 2 tempo_processador
    // 3 blocos_memoria
    // 4 numero_impressora
    // 5 requisicao_scanner
    // 6 requisicao_modem
    // 7 numero_disco
public:
    string atributos[8];

    Processo(string valores_entrada[8]);

//Funcoes para mexer com atributos de processo
    //Retorna, em inteiro, o tempo de inicializacao
    int getTempoInicializacao();

    //Recebe a prioridade do processo
    int getPrioridade();
    //Permite mudanca da prioridade de um processo dinamicamente
    void setPrioridade(int prioridade);

    //Obtencao do tempo de processador atual de um processo
    int getTempoProcessador();
    void setTempoProcessador(int tempo);

    //Obtencao e modificacao dos blocos de memoria do processo
    int getBlocos();
    void setBlocos(int blocos);

    //Retorna numero da impressora
    int getImpressora();
    //Seta numero da impressora requisitada
    void setImpressora(int impressora);

    //Verifica se Processo requsitou o Scanner
    bool getScanner();
    void setScanner(bool scanner);

    //Verifica se Processo requsitou o Modem
    bool getModem();
    void setModem(bool modem);

    //Obtencao e modificacao do numer de disco
    int getDisco();
    void setDisco(int disco);

    //Para debug
    void print();
};

#endif // PROCESS_H
