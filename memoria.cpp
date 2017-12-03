#include "memoria.h"

/* SegmentoContiguo */

// Construtor
SegmentoContiguo::SegmentoContiguo(int novo_blocos_memoria, int novo_offset_memoria, Processo *novo_processo){
    // aloca os recursos
    blocos_memoria = novo_blocos_memoria;
    offset_memoria = novo_offset_memoria;
    processo = novo_processo;
}
// Destrutor
SegmentoContiguo::~SegmentoContiguo(){
    // desaloca os recursos
}

// Get and Set blocos_memoria
int SegmentoContiguo::getBlocosMemoria(){
    return blocos_memoria;
}
void SegmentoContiguo::setBlocosMemoria(int novo_blocos_memoria){
    blocos_memoria = novo_blocos_memoria;
    return;
}
// Get and Set blocos_memoria
int SegmentoContiguo::getOffsetMemoria(){
    return offset_memoria;
}
void SegmentoContiguo::setOffsetMemoria(int novo_offset_memoria){
    offset_memoria = novo_offset_memoria;
}
// Get and Set processo
Processo* SegmentoContiguo::getProcesso(){
    return processo;
}
void SegmentoContiguo::setProcesso(Processo *novo_processo){
    processo = novo_processo;
}


/* Memoria */

// Construtor
Memoria::Memoria(){
    // inserindo os segmentos continuos com offset
    tempo_real.push_front(SegmentoContiguo(REAL_TIME,0,NULL));
    usuario.push_front(SegmentoContiguo(USER,REAL_TIME,NULL));
    
}
// Destrutor
Memoria::~Memoria(){
    // desaloca os recursos
}

// aloca memoria para um processo
void Memoria::aloca(Processo *processo){
    // blocos que o processo deseja ocupar
    int blocos_desejados = processo->getBlocos();
    // iterador para o laco
    list<SegmentoContiguo>::iterator iterador;

    // processo de tempo real
    if(!processo->getPrioridade()){
        // aloca tempo real

        // percorre o segmento de memoria procurando espaco disponivel
        for(iterador = tempo_real.begin(); iterador != tempo_real.end(); ++iterador){
            // processo quer a mesma quantidade de blocos que os disponiveis
            if(iterador->getProcesso() == NULL && iterador->getBlocosMemoria() == blocos_desejados){
                iterador->setBlocosMemoria(blocos_desejados);
                iterador->setProcesso(processo);
                processo->setMemOffset(iterador->getOffsetMemoria());
            }
            // processo quer menos blocos que os disponiveis
            if(iterador->getProcesso() == NULL && iterador->getBlocosMemoria() > blocos_desejados){
                SegmentoContiguo novo_segmento(iterador->getBlocosMemoria() - blocos_desejados, iterador->getOffsetMemoria() + blocos_desejados, NULL);
                tempo_real.insert(iterador++, novo_segmento);
            }
            // nao tem memoria disponivel
            else{
                cout << "Não existe memória disponível" << endl;
            }
        }
    }
    // processo de usuario
    else{
        // aloca usuario
    }

}
// desaloca a memoria de um processo
void Memoria::desaloca(Processo *processo){

}
// imprime o conteudo da memoria
void Memoria::print_memoria(){

}