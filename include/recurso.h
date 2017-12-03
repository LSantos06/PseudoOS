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

class Instancia{

private:
    // processo que possui a instancia
    Processo *processo_usuario;

public:
    // Construtor
    Instancia();    
    // Destrutor
    ~Instancia();

    // Get processo
    Processo* getProcessoUsuario();
    void setProcessoUsuario(Processo *novo_processo_usuario);

    // retorna o estado da insatancia
    bool estadoInstancia();
};


class Recurso{

private:
    // tipo de recurso
    Tipo tipo_recurso;
    // numero de instancias do recurso
    int numero_instancias;
    // instancias do recurso
    vector<Instancia> instancias;

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

    // reserva um recurso para um processo de usuario
    bool reservaRecurso(Processo *novo_processo_usuario);
    // libera um recurso 
    bool liberaRecurso(Processo *novo_processo_usuario);
    // imprime as instancias e seus estados
    void imprimeInstancias();
    
};

#endif