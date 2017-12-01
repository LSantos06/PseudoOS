#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

using namespace std;

int main(int argc, char *argv[]){
    /* Variaveis para manipulacao dos arquivos de entrada */
    ifstream info_processos;
    ifstream ops_sistemas_arquivos;
    string linha;

    /* Manipulacao do primeiro arquivo de entrada */
    cout << "Arquivo Info Processos\n";
    // abre o arquivo
    info_processos.open(argv[1]);
    // obtem linha a linha se o arquivo estiver aberto
    if(info_processos.is_open()){
        while(getline(info_processos,linha)){
            cout << linha << "\n";
        }
        // fecha o arquivo
        info_processos.close();
    }  
    // ERRO: arquivo nao foi aberto    
    else{
        throw runtime_error( "Não foi possível abrir o arquivo info processos" );
    }  

    /* Manipulacao do segundo arquivo de entrada */
    cout << "Arquivo Operacoes\n";
    // abre o arquivo
    ops_sistemas_arquivos.open(argv[2]);
    // obtem linha a linha se o arquivo estiver aberto
    if(ops_sistemas_arquivos.is_open()){
        while(getline(ops_sistemas_arquivos,linha)){
            cout << linha << "\n";
        }
        // fecha o arquivo
        ops_sistemas_arquivos.close();
    }  
    // ERRO: arquivo nao foi aberto
    else{
        throw runtime_error( "Não foi possível abrir o arquivo operacoes" );
    }  

    return 0;
}