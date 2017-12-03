#include <string>
#include <sstream>
#include <iostream>
#include <stdbool.h>
#include "../include/processos.h"
#include "../include/filas.h"


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

//Insercao nas filas
    FilaGlobal filaGlobal;
    cout << endl << "Tamanho: (esperado 0); Obtido "<< filaGlobal.getTamanho() << endl;
    cout << "Esta cheia? (esperado 0); Obtido " << filaGlobal.estaCheia() << endl;
    cout << "Esta vazia? (esperado 1); Obtido" << filaGlobal.estaoVazias() << endl << endl;
    cout << "******** Teste de insercoes ********" << endl;

    std::vector<Processo *> processos;

    filaGlobal.insere(&processo1);
    filaGlobal.insere(&processo2);
    filaGlobal.insere(&processo3);
    filaGlobal.insere(&processo4);

    cout << endl << "Tamanho: (esperado 4); Obtido "<< filaGlobal.getTamanho() << endl;
    cout << "Esta cheia? (esperado 0); Obtido " << filaGlobal.estaCheia() << endl;
    cout << "Esta vazia? (esperado 0); Obtido " << filaGlobal.estaoVazias() << endl << endl;

    cout << "******** Teste de remocao ********" << endl;
    Processo* processoAtual = filaGlobal.escolhe_processo();
    cout << endl << "PID: (esperado 0); Obtido "<< processoAtual->getID() << endl;
    cout << endl << "Tamanho: (esperado 3); Obtido "<< filaGlobal.getTamanho() << endl;

    cout << "******** Teste de realimentacao ********" << endl;
    filaGlobal.realimenta(processoAtual);
    cout << endl << "Tamanho: (esperado 4); Obtido "<< filaGlobal.getTamanho() << endl;
    cout << "Esta cheia? (esperado 0); Obtido " << filaGlobal.estaCheia() << endl;
    cout << "Esta vazia? (esperado 0); Obtido " << filaGlobal.estaoVazias() << endl << endl;

    return 0;
}
