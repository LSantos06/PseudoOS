#include "../include/memoria.h"

int main(){
    cout << "+_+_+_+_+_+ Testes SegmentoContiguo +_+_+_+_+_+" << endl;

    SegmentoContiguo segmento_teste(2,1,NULL);
    string atributos_teste[10] = {"0", "0", "1", "60", "0",
    "0","1","2", "1","0"};
    string atributos_teste_2[10] = {"0", "3", "2", "60", "0",
    "0","1","2", "3","0"};
    Processo processo_teste(atributos_teste);
    Processo processo_teste_2(atributos_teste_2);

    /* Teste SegmentoContiguo Get and Set */
    // Teste getBlocosMemoria()
    cout << "Teste getBlocosMemoria()" << endl;
    cout << segmento_teste.getBlocosMemoria() << endl;

    // Teste setBlocosMemoria()
    cout << "Teste setBlocosMemoria()" << endl;
    segmento_teste.setBlocosMemoria(5);
    cout << segmento_teste.getBlocosMemoria() << endl;

    // Teste getOffsetMemoria()
    cout << "Teste getOffsetMemoria()" << endl; 
    cout << segmento_teste.getOffsetMemoria() << endl;  

    // Teste getProcesso()
    cout << "Teste getProcesso()" << endl;
    segmento_teste.setProcesso(&processo_teste);
    cout << segmento_teste.getProcesso()->getTempoInicializacao() << endl;
    cout << segmento_teste.getProcesso()->getPrioridade() << endl;
    cout << segmento_teste.getProcesso()->getTempoProcessador() << endl;
    cout << segmento_teste.getProcesso()->getBlocos() << endl;
    cout << segmento_teste.getProcesso()->getImpressora() << endl;
    cout << segmento_teste.getProcesso()->getScanner() << endl;
    cout << segmento_teste.getProcesso()->getDisco() << endl;
    cout << segmento_teste.getProcesso()->getID() << endl;
    cout << segmento_teste.getProcesso()->getMemOffset() << endl;

    // Teste setProcessoUsuario()
    cout << "Teste setProcessoUsuario()" << endl;
    segmento_teste.setProcesso(&processo_teste_2);
    cout << segmento_teste.getProcesso()->getTempoInicializacao() << endl;
    cout << segmento_teste.getProcesso()->getPrioridade() << endl;
    cout << segmento_teste.getProcesso()->getTempoProcessador() << endl;
    cout << segmento_teste.getProcesso()->getBlocos() << endl;
    cout << segmento_teste.getProcesso()->getImpressora() << endl;
    cout << segmento_teste.getProcesso()->getScanner() << endl;
    cout << segmento_teste.getProcesso()->getDisco() << endl;
    cout << segmento_teste.getProcesso()->getID() << endl;
    cout << segmento_teste.getProcesso()->getMemOffset() << endl;

    cout << "+_+_+_+_+_+ Testes Memoria +_+_+_+_+_+" << endl;

    Memoria memoria_teste;
    string atributos_teste_3[10] = {"0", "0", "1", "1", "0",
    "0","1","2", "1","0"};
    string atributos_teste_4[10] = {"0", "3", "2", "10000", "0",
    "0","1","2", "3","0"};
    string atributos_teste_5[10] = {"0", "3", "2", "0", "0",
    "0","1","2", "3","0"};
    Processo processo_teste_3(atributos_teste_3);
    Processo processo_teste_4(atributos_teste_4);
    Processo processo_teste_5(atributos_teste_5);

    /* Teste Memoria Funcoes */
    // Teste aloca()
    cout << "Teste aloca()" << endl;
    cout << memoria_teste.aloca(&processo_teste) << endl;
    cout << memoria_teste.aloca(&processo_teste_3) << endl;
    //cout << memoria_teste.aloca(&processo_teste_2) << endl;
    //cout << memoria_teste.aloca(&processo_teste_4) << endl;
    //cout << memoria_teste.aloca(&processo_teste_5) << endl;
    memoria_teste.imprimeMemoria();

    // Teste desaloca()
    cout << "Teste desaloca()" << endl;
    //cout << memoria_teste.desaloca(&processo_teste) << endl;
    //cout << memoria_teste.desaloca(&processo_teste_2) << endl;
    //memoria_teste.imprimeMemoria();

    // Teste imprimeMemoria()
    //memoria_teste.imprimeMemoria();

}