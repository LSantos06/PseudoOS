#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>
#include "entrada.h"

using namespace std;

int main(int argc, char *argv[]){
    /* Variaveis para manipulacao dos arquivos de entrada */
    ifstream info_processos;
    ifstream ops_sistemas_arquivos;

    /* Classes para o armazenamento dos dados dos arquivos */
    string linha;
    string token;    
    int i;
    Processo aux_processo;
    ArqInfoProcessos arq_info_processos;
    ArqOpsSistemasArquivos arq_ops_sistemas_arquivos;

    /* Manipulacao do primeiro arquivo de entrada */
    cout << "Arquivo Info Processos" << endl;
    // abre o arquivo
    info_processos.open(argv[1]);
    // obtem linha a linha se o arquivo estiver aberto
    if(info_processos.is_open()){
        while(getline(info_processos,linha)){
            cout << linha << endl;
            // separacao dos atributos da linha para um processo
            istringstream iss(linha);
            i = 0;
            while (getline(iss, token, ',')){
                cout << token << endl;
                i++;
            }
            // insere novo processo na lista de processos do arquivo
            //arq_info_processos.processos.push_front(aux_processo);
        }
        // fecha o arquivo
        info_processos.close();
    }  
    // ERRO: arquivo nao foi aberto    
    else{
        throw runtime_error( "Não foi possível abrir o arquivo info processos" );
    }  

    /* Manipulacao do segundo arquivo de entrada */
    cout << "Arquivo Operacoes" << endl;
    // abre o arquivo
    ops_sistemas_arquivos.open(argv[2]);
    // obtem linha a linha se o arquivo estiver aberto
    if(ops_sistemas_arquivos.is_open()){
        while(getline(ops_sistemas_arquivos,linha)){
            cout << linha << endl;
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