#ifndef MEMORIA_H
#define MEMORIA_H

#include <list>
#include <iterator>
#include "processos.h"

#define MEM_SIZE 1024
#define REAL_TIME 64
#define USER 960

using namespace std;

class SegmentoContiguo{

private:
    // blocos contiguos
    int blocos_memoria;
    // offset do inicio da memoria
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
    // Get and Set blocos_memoria
    int getOffsetMemoria();
    void setOffsetMemoria(int novo_offset_memoria);
    // Get and Set processo
    Processo* getProcesso();
    void setProcesso(Processo *novo_processo);        

};

class Memoria{

private:
    // segmentos contiguos de processo de tempo real (MAX 64)
    list<SegmentoContiguo> tempo_real;
    // segmentos contiguos de processo de usuario (MAX 960)
    list<SegmentoContiguo> usuario; 

public:
    // Construtor
    Memoria();
    // Destrutor
    ~Memoria();

    // aloca memoria para um processo
    void aloca(Processo *processo);
    // desaloca a memoria de um processo
    void desaloca(Processo *processo);
    // imprime o conteudo da memoria
    void print_memoria();
};

#endif
