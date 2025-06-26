#ifndef RODADA_H
#define RODADA_H

#include <vector>
#include "usuario.h"
#include "jogador.h"

class Rodada {
public:
    int numero;
    Rodada();
    Rodada(int numero);
    void atualizarPontuacoes(std::vector<Usuario>& usuarios, const std::vector<Jogador>& jogadoresAtualizados);
};

#endif