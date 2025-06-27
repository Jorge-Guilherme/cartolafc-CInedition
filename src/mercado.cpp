#include "mercado.h"
#include <iostream>
#include <json.hpp>

Mercado::Mercado() {}

void Mercado::listarJogadores() const {
    std::cout << "ID\tNome\t\tPosição\t\tPreço\n";
    for (const auto& j : jogadoresDisponiveis) {
        std::cout << j.getId() << "\t" << j.getNome() << "\t" << j.getPosicao() << "\t" << j.getPreco() << "\n";
    }
}

bool Mercado::comprarJogador(int jogadorId, double& saldo, std::vector<Jogador>& time) {
    for (const auto& j : jogadoresDisponiveis) {
        if (j.getId() == jogadorId && saldo >= j.getPreco()) {
            time.push_back(j);
            saldo -= j.getPreco();
            return true;
        }
    }
    return false;
}

bool Mercado::venderJogador(int jogadorId, double& saldo, std::vector<Jogador>& time) {
    for (auto it = time.begin(); it != time.end(); ++it) {
        if (it->getId() == jogadorId) {
            saldo += it->getPreco();
            time.erase(it);
            return true;
        }
    }
    return false;
}