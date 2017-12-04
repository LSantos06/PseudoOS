#include "../include/recurso.h"

int main(){
    cout << "+_+_+_+_+_+ Testes Instancia +_+_+_+_+_+" << endl;

    Instancia instancia_teste;
    string atributos_teste[10] = {"0", "1", "1", "0", "0",
    "0","1","2", "1","0"};
    string atributos_teste_2[10] = {"0", "3", "2", "0", "0",
    "0","1","2", "3","0"};
    Processo processo_teste(atributos_teste);
    Processo processo_teste_2(atributos_teste_2);

    /* Teste Instancia Get and Set */
    // Teste getProcessoUsuario()
    cout << "Teste getProcessoUsuario()" << endl;
    instancia_teste.setProcessoUsuario(&processo_teste);
    cout << instancia_teste.getProcessoUsuario()->getTempoInicializacao() << endl;
    cout << instancia_teste.getProcessoUsuario()->getPrioridade() << endl;
    cout << instancia_teste.getProcessoUsuario()->getTempoProcessador() << endl;
    cout << instancia_teste.getProcessoUsuario()->getBlocos() << endl;
    cout << instancia_teste.getProcessoUsuario()->getImpressora() << endl;
    cout << instancia_teste.getProcessoUsuario()->getScanner() << endl;
    cout << instancia_teste.getProcessoUsuario()->getDisco() << endl;
    cout << instancia_teste.getProcessoUsuario()->getID() << endl;
    cout << instancia_teste.getProcessoUsuario()->getMemOffset() << endl;

    // Teste setProcessoUsuario()
    cout << "Teste setProcessoUsuario()" << endl;
    instancia_teste.setProcessoUsuario(&processo_teste_2);
    cout << instancia_teste.getProcessoUsuario()->getTempoInicializacao() << endl;
    cout << instancia_teste.getProcessoUsuario()->getPrioridade() << endl;
    cout << instancia_teste.getProcessoUsuario()->getTempoProcessador() << endl;
    cout << instancia_teste.getProcessoUsuario()->getBlocos() << endl;
    cout << instancia_teste.getProcessoUsuario()->getImpressora() << endl;
    cout << instancia_teste.getProcessoUsuario()->getScanner() << endl;
    cout << instancia_teste.getProcessoUsuario()->getDisco() << endl;
    cout << instancia_teste.getProcessoUsuario()->getID() << endl;
    cout << instancia_teste.getProcessoUsuario()->getMemOffset() << endl;

    /* Teste Instancia Funcoes */
    // Teste estadoInstancia()
    cout << "Teste estadoInstancia()" << endl;
    cout << instancia_teste.estadoInstancia() << endl;
    instancia_teste.setProcessoUsuario(NULL);
    cout << instancia_teste.estadoInstancia() << endl;  

    cout << "+_+_+_+_+_+ Testes Recurso +_+_+_+_+_+" << endl;

    Recurso recurso_teste(SATA, 2);

    /* Teste Recurso Get and Set */
    // Teste getTipoRecurso()
    cout << "Teste getTipoRecurso()" << endl;
    cout << recurso_teste.getTipoRecurso() << endl;

    // Teste getNumeroInstancias()
    cout << "Teste getNumeroInstancias()" << endl;
    cout << recurso_teste.getNumeroInstancias() << endl;

    // Teste setNumeroInstancias()
    cout << "Teste setNumeroInstancias()" << endl;
    recurso_teste.setNumeroInstancias(1);
    cout << recurso_teste.getNumeroInstancias() << endl;
    recurso_teste.setNumeroInstancias(2);
    cout << recurso_teste.getNumeroInstancias() << endl;

    /* Teste Recurso Funcoes */
    // Teste reservaRecurso()
    cout << "Teste reservaRecurso()" << endl;
    cout << recurso_teste.reservaRecurso(&processo_teste) << endl;
    cout << recurso_teste.reservaRecurso(&processo_teste_2) << endl;
    cout << recurso_teste.reservaRecurso(&processo_teste) << endl;

    // Teste liberaRecurso()
    cout << "Teste liberaRecurso()" << endl;    
    cout << recurso_teste.liberaRecurso(&processo_teste) << endl;
    cout << recurso_teste.liberaRecurso(&processo_teste_2) << endl;
    cout << recurso_teste.liberaRecurso(&processo_teste) << endl;

    // Teste imprimeInstancias()
    cout << "Teste imprimeInstancias()" << endl;
    recurso_teste.imprimeInstancias();
    cout << recurso_teste.reservaRecurso(&processo_teste_2) << endl;
    recurso_teste.imprimeInstancias();

    return 0;
}