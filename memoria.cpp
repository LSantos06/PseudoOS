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
// Get offset_memoria
int SegmentoContiguo::getOffsetMemoria(){
    return offset_memoria;
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
    // aloca os recursos
    tempo_real.push_back(SegmentoContiguo(REAL_TIME,0,NULL));
    usuario.push_back(SegmentoContiguo(USER,REAL_TIME,NULL));
    
}
// Destrutor
Memoria::~Memoria(){
    // desaloca os recursos
}

// aloca memoria para um processo
bool Memoria::aloca(Processo *processo){
    // blocos que o processo deseja ocupar
    int blocos_desejados = processo->getBlocos();
    // iterador para o laco
    vector<SegmentoContiguo>::iterator segmento_atual;

    // processo de tempo real
    if(!processo->getPrioridade()){
        // aloca tempo real

        // percorre o segmento de memoria procurando espaco disponivel
        for(segmento_atual = tempo_real.begin(); segmento_atual != tempo_real.end(); ++segmento_atual){
            // processo quer a mesma quantidade de blocos que os disponiveis
            if(segmento_atual->getProcesso() == NULL && segmento_atual->getBlocosMemoria() == blocos_desejados){
                // da o segmento ao processo
                segmento_atual->setBlocosMemoria(blocos_desejados);
                segmento_atual->setProcesso(processo);
                processo->setMemOffset(segmento_atual->getOffsetMemoria());
            }
            // processo quer menos blocos que os disponiveis
            if(segmento_atual->getProcesso() == NULL && segmento_atual->getBlocosMemoria() > blocos_desejados){
                // da o segmento ao processo
                segmento_atual->setBlocosMemoria(blocos_desejados);
                segmento_atual->setProcesso(processo);
                processo->setMemOffset(segmento_atual->getOffsetMemoria());
                // insercao do segmento na lista
                tempo_real.insert(next(segmento_atual), SegmentoContiguo(segmento_atual->getBlocosMemoria() - blocos_desejados, segmento_atual->getOffsetMemoria() + blocos_desejados, NULL));
            }
            cout << "Processo alocado! (tempo real)" << endl;
            return true;
        }
    }
    // processo de usuario
    else{
        // aloca usuario

        // percorre o segmento de memoria procurando espaco disponivel
        for(segmento_atual = usuario.begin(); segmento_atual != usuario.end(); ++segmento_atual){
            // processo quer a mesma quantidade de blocos que os disponiveis
            if(segmento_atual->getProcesso() == NULL && segmento_atual->getBlocosMemoria() == blocos_desejados){
                // da o segmento ao processo
                segmento_atual->setBlocosMemoria(blocos_desejados);
                segmento_atual->setProcesso(processo);
                processo->setMemOffset(segmento_atual->getOffsetMemoria());
            }
            // processo quer menos blocos que os disponiveis
            if(segmento_atual->getProcesso() == NULL && segmento_atual->getBlocosMemoria() > blocos_desejados){
                // da o segmento ao processo
                segmento_atual->setBlocosMemoria(blocos_desejados);
                segmento_atual->setProcesso(processo);
                processo->setMemOffset(segmento_atual->getOffsetMemoria());
                // insercao do segmento na lista
                usuario.insert(next(segmento_atual), SegmentoContiguo(segmento_atual->getBlocosMemoria() - blocos_desejados, segmento_atual->getOffsetMemoria() + blocos_desejados, NULL));              
            }
            cout << "Processo alocado! (usuario)" << endl;
            return true;
        }
    }
    cout << "Não foi possível alocar o processo!" << endl;
    return false;
}
// desaloca a memoria de um processo
bool Memoria::desaloca(Processo *processo){
    // iterador para o laco
    vector<SegmentoContiguo>::iterator segmento_atual;

    // processo de tempo real
    if(!processo->getPrioridade()){
        // percorre o segmento de memoria procurando espaco disponivel
        for(segmento_atual = tempo_real.begin(); segmento_atual != tempo_real.end(); ++segmento_atual){
            // processo que quer desalocar
            if(segmento_atual->getProcesso() == processo){
                // retira o processo da memoria
                segmento_atual->setProcesso(NULL);
                // se retirar do comeco
                if(segmento_atual == tempo_real.begin()){
                    // se o proximo elemento nao tiver processo
                    if(next(segmento_atual)->getProcesso() == NULL){
                        // aumenta a quantidade de blocos disponivel
                        segmento_atual->setBlocosMemoria(segmento_atual->getBlocosMemoria() + segmento_atual->getProcesso()->getBlocos());
                        cout << "Processo desalocado!" << endl;
                        return true;
                    }
                    // se o proximo elemento tiver processo, memoria nao sera mais contigua
                    else{
                        cout << "Não foi possível desalocar o processo!" << endl;
                        return false;
                    }
                }
                // se retirar do meio
                if(segmento_atual != tempo_real.begin() && segmento_atual != tempo_real.end()){
                    // se o proximo elemento nao tiver processo
                    if(next(segmento_atual)->getProcesso() == NULL){
                        // aumenta a quantidade de blocos disponivel
                        segmento_atual->setBlocosMemoria(segmento_atual->getBlocosMemoria() + segmento_atual->getProcesso()->getBlocos());
                        cout << "Processo desalocado!" << endl;
                        return true;
                    }
                    // se o proximo elemento tiver processo, memoria nao sera mais contigua
                    else{
                        cout << "Não foi possível desalocar o processo!" << endl;
                        return false;
                    }
                }
                // se retirar do fim
                if(segmento_atual == tempo_real.end()){
                    // se o elemento anterior nao tiver processo
                    if(prev(segmento_atual)->getProcesso() == NULL){
                        // aumenta a quantidade de blocos disponivel
                        segmento_atual->setBlocosMemoria(segmento_atual->getBlocosMemoria() + segmento_atual->getProcesso()->getBlocos());
                        cout << "Processo desalocado!" << endl;
                        return true;
                    }
                    // se o elemento anterior tiver processo, memoria nao sera mais contigua
                    else{
                        cout << "Não foi possível desalocar o processo!" << endl;
                        return false;
                    }
                }
            }
        }    
    }
    // processo de usuario
    else{
        // percorre o segmento de memoria procurando espaco disponivel
        for(segmento_atual = usuario.begin(); segmento_atual != usuario.end(); ++segmento_atual){
            // processo que quer desalocar
            if(segmento_atual->getProcesso() == processo){
                // retira o processo da memoria
                segmento_atual->setProcesso(NULL);
                // se retirar do comeco
                if(segmento_atual == tempo_real.begin()){
                    // se o proximo elemento nao tiver processo
                    if(next(segmento_atual)->getProcesso() == NULL){
                        // aumenta a quantidade de blocos disponivel
                        segmento_atual->setBlocosMemoria(segmento_atual->getBlocosMemoria() + segmento_atual->getProcesso()->getBlocos());
                        cout << "Processo desalocado!" << endl;
                        return true;
                    }
                    // se o proximo elemento tiver processo, memoria nao sera mais contigua
                    else{
                        cout << "Não foi possível desalocar o processo!" << endl;
                        return false;
                    }
                }
                // se retirar do meio
                if(segmento_atual != tempo_real.begin() && segmento_atual != tempo_real.end()){
                    // se o proximo elemento nao tiver processo
                    if(next(segmento_atual)->getProcesso() == NULL){
                        // aumenta a quantidade de blocos disponivel
                        segmento_atual->setBlocosMemoria(segmento_atual->getBlocosMemoria() + segmento_atual->getProcesso()->getBlocos());
                        cout << "Processo desalocado!" << endl;
                        return true;
                    }
                    // se o proximo elemento tiver processo, memoria nao sera mais contigua
                    else{
                        cout << "Não foi possível desalocar o processo!" << endl;
                        return false;
                    }
                }
                // se retirar do fim
                if(segmento_atual == tempo_real.end()){
                    // se o elemento anterior nao tiver processo
                    if(prev(segmento_atual)->getProcesso() == NULL){
                        // aumenta a quantidade de blocos disponivel
                        segmento_atual->setBlocosMemoria(segmento_atual->getBlocosMemoria() + segmento_atual->getProcesso()->getBlocos());
                        cout << "Processo desalocado!" << endl;
                        return true;
                    }
                    // se o elemento anterior tiver processo, memoria nao sera mais contigua
                    else{
                        cout << "Não foi possível desalocar o processo!" << endl;
                        return false;
                    }
                }
            }
        } 
    }
    cout << "Não foi possível desalocar o processo!" << endl;
    return false;
}
// imprime o conteudo da memoria
void Memoria::imprimeMemoria(){
    cout << "+_+_+_+_+_+ Memoria +_+_+_+_+_+" << endl;

    // iterador para o laco
    vector<SegmentoContiguo>::iterator segmento_atual;

    /* Blocos de tempo real */
    cout << "+_+ Blocos de tempo real +_+:" << endl;

    // percorre o segmento de memoria procurando espaco disponivel
    for(segmento_atual = tempo_real.begin(); segmento_atual != tempo_real.end(); ++segmento_atual){
        cout << "Posicao Memoria: " << segmento_atual->getOffsetMemoria() << " ";
        cout << "Blocos Ocupados: "  << segmento_atual->getBlocosMemoria() << " ";
        // se possui processo ocupando
        if(segmento_atual->getProcesso()){
            cout << "ID Processo: " << segmento_atual->getProcesso()->getID() << " ";
            cout << "Posicao Memoria Processo: "  << segmento_atual->getProcesso()->getMemOffset() << " ";
            cout << "Blocos Memoria Processo: "  << segmento_atual->getProcesso()->getBlocos() << " ";
        }
        // se nao possui processo ocupando
        else{
            cout << "Sem Processo" << endl;
        }
    }

    /* Blocos de usuario */
    cout << "+_+ Blocos de usuario +_+:" << endl;

    // percorre o segmento de memoria procurando espaco disponivel
    for(segmento_atual = usuario.begin(); segmento_atual != usuario.end(); ++segmento_atual){
        cout << "Posicao Memoria: " << segmento_atual->getOffsetMemoria() << " ";
        cout << "Blocos Ocupados: "  << segmento_atual->getBlocosMemoria() << " ";
        // se possui processo ocupando
        if(segmento_atual->getProcesso()){
            cout << "ID Processo: " << segmento_atual->getProcesso()->getID() << " ";
            cout << "Posicao Memoria Processo: "  << segmento_atual->getProcesso()->getMemOffset() << " ";
            cout << "Blocos Memoria Processo: "  << segmento_atual->getProcesso()->getBlocos() << " ";
        }
        // se nao possui processo ocupando
        else{
            cout << "Sem Processo" << endl;
        }
    }

}