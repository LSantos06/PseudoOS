#ifndef MEMORIA_H
#define MEMORIA_H

#include <vector>
#include <iterator>
#include "processos.h"

#define REAL_TIME 64
#define USER 960

using namespace std;

// Classe que representa a memória
class Memoria{

private:
    // memoria em si
    int memoria[REAL_TIME+USER];

public:
    // Construtor
    Memoria();
    // Destrutor
    ~Memoria();

    // verifica se tem memoria contigua para um processo
    int verifica(int quantidade_blocos, int comeco, int fim);
    // aloca uma quantidade de blocos para a memoria 
    int aloca(int quantidade_blocos, Processo *processo);
    // desaloca uma quantidade de blocos para a memoria
    void desaloca(int offset, int quantidade_blocos);
    // imprime o conteudo da memoria
    void imprimeMemoria();
};

#endif
