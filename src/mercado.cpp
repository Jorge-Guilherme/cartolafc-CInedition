#include "mercado.h"
#include <iostream>
#include <json.hpp>

Mercado::Mercado() {}

void Mercado::listarJogadores() const {
    std::cout << "ID\tNome\t\tPosição\t\tPreço\n";
    for (const auto& j : jogadoresDisponiveis) {
        std::cout << j.id << "\t" << j.nome << "\t" << j.posicao << "\t" << j.preco << "\n";
    }
}

bool Mercado::comprarJogador(int jogadorId, double& saldo, std::vector<Jogador>& time) {
    for (const auto& j : jogadoresDisponiveis) {
        if (j.id == jogadorId && saldo >= j.preco) {
            time.push_back(j);
            saldo -= j.preco;
            return true;
        }
    }
    return false;
}

bool Mercado::venderJogador(int jogadorId, double& saldo, std::vector<Jogador>& time) {
    for (auto it = time.begin(); it != time.end(); ++it) {
        if (it->id == jogadorId) {
            saldo += it->preco;
            time.erase(it);
            return true;
        }
    }
    return false;
}