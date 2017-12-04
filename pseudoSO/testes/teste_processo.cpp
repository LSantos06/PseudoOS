#include <string>
#include <sstream>
#include <iostream>
#include <stdbool.h>
#include "../include/processos.h"


using namespace std;

int main(){

    string atributos1[10];

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
    atributos1[0] = "0";
    atributos1[1] = "0";
    atributos1[2] = "5";
    atributos1[3] = "10";
    atributos1[4] = "1";
    atributos1[5] = "0";
    atributos1[6] = "1";
    atributos1[7] = "5";
    atributos1[8] = "0";
    atributos1[9] = "0";

    string atributos2[10] = {"0", "1", "1", "0", "0",
  "0","1","2", "1","0"};
  string atributos3[10] = {"0", "2", "1", "0", "0",
"0","1","2", "2","0"};
string atributos4[10] = {"0", "3", "2", "0", "0",
"0","1","2", "3","0"};


    Processo processo1(atributos1);
    Processo processo2(atributos2);
    Processo processo3(atributos3);
    Processo processo4(atributos4);

    cout << "******** Processo 1 ********" << endl;
    cout << "Inicializacao - Esperado: 0 " << "obtido: " << processo1.getTempoInicializacao() << endl;
    cout << "Prioridade - Esperado: 0 " << "obtido: " << processo1.getPrioridade() << endl;
    cout << "Processador - Esperado: 5 " << "obtido: " << processo1.getTempoProcessador() << endl;
    cout << "Blocos de memoria - Esperado: 10 " << "obtido: " << processo1.getBlocos() << endl;
    cout << "Numero impressora - Esperado: 1 " << "obtido: " << processo1.getImpressora() << endl;
    cout << "Scanner - Esperado: 0 " << "obtido: " << processo1.getScanner() << endl;
    cout << "Modem - Esperado: 1 " << "obtido: " << processo1.getModem() << endl;
    cout << "Numero de Disco - Esperado: 5 " << "obtido: " << processo1.getDisco() << endl;
    cout << "PID - Esperado: 0 " << "obtido: " << processo1.getID() << endl;
    cout << "Memory Offset - Esperado: 0 " << "obtido: " << processo1.getMemOffset() << endl << endl;

    cout << "******** Teste de insercoes ********" << endl;
    processo1.setPrioridade(1);
    processo1.setTempoProcessador(4);
    processo1.setBlocos(3);
    processo1.setImpressora(2);
    processo1.setScanner(true);
    processo1.setModem(false);
    processo1.setDisco(10);
    processo1.setMemOffset(31);
    cout << "Prioridade - Esperado: 1 " << "obtido: " << processo1.getPrioridade() << endl;
    cout << "Processador - Esperado: 4 " << "obtido: " << processo1.getTempoProcessador() << endl;
    cout << "Blocos de memoria - Esperado: 3 " << "obtido: " << processo1.getBlocos() << endl;
    cout << "Numero impressora - Esperado: 2 " << "obtido: " << processo1.getImpressora() << endl;
    cout << "Scanner - Esperado: 1 " << "obtido: " << processo1.getScanner() << endl;
    cout << "Modem - Esperado: 0 " << "obtido: " << processo1.getModem() << endl;
    cout << "Numero de Disco - Esperado: 10 " << "obtido: " << processo1.getDisco() << endl;
    cout << "PID - Esperado: 0 " << "obtido: " << processo1.getID() << endl;
    cout << "Memory Offset - Esperado: 31 " << "obtido: " << processo1.getMemOffset() << endl;
    cout << "Eh usuario? (Espera-se 1) " << "obtido: " << processo1.eh_usuario() << endl;


    return 0;
}
