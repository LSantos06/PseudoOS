#ifndef RECURSO_H
#define RECURSO_H

#include <vector>
#include "processos.h"

// tipagem para o tipo de recurso
typedef enum tipo{
    SCANNER,
    IMPRESSORA,
    MODEM,
    SATA
} Tipo;

class Recurso{

private:
    // tipo de recurso
    Tipo tipo_recurso;
    // numero de instancias do recurso
    int numero_instancias;
    // instancias do recurso
    vector<int> instancias;
    // processo de usuario que detem o recurso
    Processo *processo_usuario; 

public:
    // Construtor
    Recurso(Tipo tipo_recurso, int numero_instancias);    
    // Destrutor
    ~Recurso();

    // Get tipo_recurso
    Tipo getTipoRecurso();
    // Get and Set numero_instancias
    int getNumeroInstancias();
    void setNumeroInstancias(int novo_numero_instancias);
    // Get and Set instancias
    vector<int> getInstancias();
    void setInstancia(int instancia, int novo_valor_instancia);
    // Get and Set processo
    Processo* getProcesso();
    void setProcesso(Processo *novo_processo_usuario);

    // reserva um recurso para um processo de usuario
    bool reservaRecurso(Processo *processo_usuario);
    // libera um recurso 
    void liberaRecurso();
    // verifica o estado de um recurso
    bool estadoRecurso();
    // imprime as instancias e seus estados
    void imprimeInstancias();
    
};

#endif