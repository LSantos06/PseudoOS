#ifndef PROCESSOS_H
#define PROCESSOS_H

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
    // 8 ProcessoID
    // 9 memory_offset
public:
    string atributos[10];

    Processo(string valores_entrada[10]);

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

    //ID do processo (apenas acesso)
    int getID();

    //Obtencao do offset de memoria do processo
    int getMemOffset();
    void setMemOffset(int offset);

    //Para debug
    void print();

    //Verifica se processo eh usuario
    bool eh_usuario();
};

#endif // PROCESS_H
