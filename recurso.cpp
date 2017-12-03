#include "recurso.h"

/* Instancia */

// Construtor
Instancia::Instancia(){
    // aloca os recursos
    processo_usuario = NULL;
}    
// Destrutor
Instancia::~Instancia(){
    // desaloca recursos
}

// Get and Set processo
Processo* Instancia::getProcessoUsuario(){
    return processo_usuario;
}
void Instancia::setProcessoUsuario(Processo *novo_processo_usuario){
    processo_usuario = novo_processo_usuario;
}

// retorna o estado da instancia
bool Instancia::estadoInstancia(){
    // se possui um processo esta ocupada
    if(processo_usuario){
        return false;
    }
    return true;
}

/* Recurso */

// Construtor
Recurso::Recurso(Tipo novo_tipo_recurso, int novo_numero_instancias){
    // aloca os recursos
    tipo_recurso = novo_tipo_recurso;
    for(int i = 0; i < novo_numero_instancias; i++){
        instancias.push_back(Instancia());
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

// reserva um recurso para um processo de usuario
bool Recurso::reservaRecurso(Processo *novo_processo_usuario){
    //TODO: Thread

    // iterador para percorrer
    vector<Instancia>::iterator instancia_atual;

    // procura uma instancia sem processo
    for(instancia_atual = instancias.begin(); instancia_atual != instancias.end(); ++instancia_atual){
        // instancia nao possui processo
        if(instancia_atual->estadoInstancia()){
            instancia_atual->setProcessoUsuario(novo_processo_usuario);
            cout << "Instancia reservada!" << endl;
            return true;
        }
    }  
    cout << "Instancia nao pode reservada!" << endl;
    return false;
}
// libera um recurso 
bool Recurso::liberaRecurso(Processo *novo_processo_usuario){
    //TODO: Thread

    // iterador para percorrer
    vector<Instancia>::iterator instancia_atual;

    // procura uma instancia sem processo
    for(instancia_atual = instancias.begin(); instancia_atual != instancias.end(); ++instancia_atual){
        // instancia nao possui processo
        if(instancia_atual->getProcessoUsuario() == novo_processo_usuario){
            instancia_atual->setProcessoUsuario(NULL);
            cout << "Instancia livre!" << endl;
            return true;
        }
    }  
    cout << "Instancia nao pode liberada!" << endl;
    return false;
}
// imprime as instancias e seus estados
void Recurso::imprimeInstancias(){
    cout << "+_+_+_+_+_+ Recurso " << tipo_recurso << " +_+_+_+_+_+" << endl;

    // iterador para o laco
    vector<Instancia>::iterator instancia_atual;

    // percorre e imprime as instancias
    for(instancia_atual = instancias.begin(); instancia_atual != instancias.end(); ++instancia_atual){
        // instancia nao possui processo
        if(instancia_atual->estadoInstancia()){
            cout << "Instancia ocupada!" << endl;
        }
        // instancia possui processo
        else{
            cout << "Instancia livre!" << endl;
        }
    }  
}