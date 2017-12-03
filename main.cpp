#include <string>
#include <sstream>
#include <iostream>
#include <stdbool.h>
#include "dispatcher.h"


using namespace std;

bool isTrue(string *atributos);

int main(){

    string atributos1[10];

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

/*    //Faz uma conversao de um tipo string para int
    stringstream convert(atributos[0]);

    int retorno;
    if(!(convert >> retorno)){
      retorno = 0;
    }

    cout << "retorno = " << retorno << endl;

    if(isTrue(atributos)){
      cout << "true" << endl;
    }
    else{
      cout << "false" << endl;
    }
*/
    Processo processo1(atributos1);
    Processo processo2(atributos2);
    Processo processo3(atributos3);
    Processo processo4(atributos4);

    //processo1.print();

    /*FilaGlobal filaGlobal;

    cout << endl << filaGlobal.getTamanho() << endl;
    cout << "Esta cheia?" << filaGlobal.estaCheia() << endl;
    cout << "Esta vazia?" << filaGlobal.estaoVazias() << endl;*/
    /*
    filaGlobal.insere(&processo1);
    cout << "Processo " << processo1.getID() << " eh usuario? " << processo1.eh_usuario() << endl;
    filaGlobal.insere(&processo2);
    cout << "Processo " << processo2.getID() << " eh usuario? " << processo2.eh_usuario() << endl;
    filaGlobal.insere(&processo3);
    cout << "Processo " << processo3.getID() << " eh usuario? " << processo3.eh_usuario() << endl;
    filaGlobal.insere(&processo4);
    cout << "Processo " << processo4.getID() << " eh usuario? " << processo4.eh_usuario() << endl;
    cout << endl << filaGlobal.getTamanho() << endl;

    cout << "Esta cheia?" << filaGlobal.estaCheia() << endl;
    cout << "Esta vazia?" << filaGlobal.estaoVazias() << endl;

    cout << "dispatcher => " << endl;
    processo1.print();
    */
    vector <Processo*> processos;
    processos.push_back(&processo1);
    processos.push_back(&processo2);
    processos.push_back(&processo3);
    processos.push_back(&processo4);

    Disco *disco = montarDisco("files.txt");
    Dispatcher dispatcher(processos, disco);

    dispatcher.executa();

    return 0;
}
