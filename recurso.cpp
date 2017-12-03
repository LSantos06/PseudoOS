#include "recurso.h"

// Construtor
Recurso::Recurso(Tipo novo_tipo_recurso, int novo_numero_instancias){
    // aloca os recursos
    tipo_recurso = novo_tipo_recurso;
    for(int i = 0; i < novo_numero_instancias; i++){
        instancias.push_back(0);
    }
}    
// Destrutor
Recurso::~Recurso(){
    // desaloca recursos
}

// Get tipo_recurso
Tipo Recurso::getTipoRecurso(){
    return tipo_recurso;
}
// Get and Set numero_instancias
int Recurso::getNumeroInstancias(){
    return numero_instancias;
}
void Recurso::setNumeroInstancias(int novo_numero_instancias){
    numero_instancias = novo_numero_instancias;
}
// Get and Set instancias
vector<int> Recurso::getInstancias(){
    return instancias;
}
void Recurso::setInstancia(int instancia, int novo_valor_instancia){
    instancias.at(instancia) = novo_valor_instancia;
}
// Get and Set processo
Processo* Recurso::getProcesso(){
    return processo_usuario;
}
void Recurso::setProcesso(Processo *novo_processo_usuario){
    processo_usuario = novo_processo_usuario;
}

// reserva um recurso para um processo de usuario
bool Recurso::reservaRecurso(Processo *processo_usuario){

}
// libera um recurso 
void Recurso::liberaRecurso(){

}
// verifica o estado de um recurso
bool Recurso::estadoRecurso(){

}
// imprime as instancias e seus estados
void Recurso::imprimeInstancias(){

}