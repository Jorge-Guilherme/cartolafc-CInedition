#include "usuario.h"
#include <json.hpp>

Usuario::Usuario() : id(0), saldo(100.0), timeEscalado() {}

Usuario::Usuario(int id, const std::string& nome, double saldo, const TimeEscalado& timeEscalado)
    : id(id), nome(nome), saldo(saldo), timeEscalado(timeEscalado) {}

void Usuario::comprarJogador(const Jogador& jogador) {
    if (saldo >= jogador.preco) {
        timeEscalado.adicionarJogador(jogador);
        saldo -= jogador.preco;
    }
}

void Usuario::venderJogador(int jogadorId) {
    for (const auto& j : timeEscalado.titulares) {
        if (j.id == jogadorId) {
            saldo += j.preco;
            break;
        }
    }
    timeEscalado.removerJogador(jogadorId);
}

void Usuario::escalarTime(const std::vector<int>& jogadoresIds) {
    // Implementar lógica de escalação
}