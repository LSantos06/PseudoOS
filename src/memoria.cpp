#include "../include/memoria.h"

/* Memoria */

// Construtor
Memoria::Memoria(){
    for(int i = 0; i < (REAL_TIME+USER); i++){
        memoria[i] = 0;
    }       
}
// Destrutor
Memoria::~Memoria(){
    // desaloca os recursos
}

// verifica se tem memoria contigua para um processo
int Memoria::verifica(int quantidade_blocos, int comeco, int fim){

}
// aloca memoria para um processo
int Memoria::aloca(int quantidade_blocos, Processo *processo){

}
// desaloca a memoria
void Memoria::desaloca(int offset, int quantidade_blocos){
    // percorre e zera a memoria
    for(int i = offset; i < (quantidade_blocos+offset); i++){
        memoria[i] = 0;
    }  
}
// imprime o conteudo da memoria
void Memoria::imprimeMemoria(){
    cout << "+_+_+_+_+_+ Memoria +_+_+_+_+_+" << endl;

    // percorre e imprime a memoria
    for(int i = 0; i < (REAL_TIME+USER); i++){
        cout << memoria[i];
    }  
    cout << endl;
}