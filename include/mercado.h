#ifndef MERCADO_H
#define MERCADO_H

#include <vector>
#include "jogador.h"

class Mercado {
public:
    std::vector<Jogador> jogadoresDisponiveis;

    Mercado();
    void listarJogadores() const;
    bool comprarJogador(int jogadorId, double& saldo, std::vector<Jogador>& time);
    bool venderJogador(int jogadorId, double& saldo, std::vector<Jogador>& time);
};

#endif