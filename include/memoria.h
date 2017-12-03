#ifndef MEMORIA_H
#define MEMORIA_H

#include <vector>
#include <iterator>
#include "processos.h"

#define REAL_TIME 64
#define USER 960

using namespace std;

// Classe que representa um conjunto de blocos contiguos
class SegmentoContiguo{

private:
    // blocos contiguos
    int blocos_memoria;
    // offset do inicio do segmento contiguo
    int offset_memoria;
    // processo dono do segmento contiguo
    Processo *processo; 

public:
    // Construtor
    SegmentoContiguo(int blocos_memoria, int offset_memoria, Processo *processo);    
    // Destrutor
    ~SegmentoContiguo();

    // Get and Set blocos_memoria
    int getBlocosMemoria();
    void setBlocosMemoria(int novo_blocos_memoria);
    // Get and Set offset_memoria
    int getOffsetMemoria();
    // Get and Set processo
    Processo* getProcesso();
    void setProcesso(Processo *novo_processo);        

};

// Classe que representa a memória
class Memoria{

private:
    // segmentos contiguos de processo de tempo real 
    vector<SegmentoContiguo> tempo_real;
    // segmentos contiguos de processo de usuario
    vector<SegmentoContiguo> usuario; 

public:
    // Construtor
    Memoria();
    // Destrutor
    ~Memoria();

    // aloca memoria para um processo
    bool aloca(Processo *processo);
    // desaloca a memoria de um processo
    bool desaloca(Processo *processo);
    // imprime o conteudo da memoria
    void imprimeMemoria();
};

#endif
