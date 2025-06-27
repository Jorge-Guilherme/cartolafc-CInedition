#include "usuario.h"
#include <json.hpp>
#include <iostream>

// Construtor padrão
Usuario::Usuario() : Pessoa(0, ""), saldo(100.0), timeEscalado() {}

// Construtor parametrizado
Usuario::Usuario(int id, const std::string& nome, double saldo, const TimeEscalado& timeEscalado)
    : Pessoa(id, nome), saldo(saldo), timeEscalado(timeEscalado) {}

void Usuario::comprarJogador(const Jogador& jogador) {
    if (saldo >= jogador.getPreco()) {
        timeEscalado.adicionarJogador(jogador);
        saldo -= jogador.getPreco();
    }
}

void Usuario::venderJogador(int jogadorId) {
    for (const auto& j : timeEscalado.getComprados()) {
        if (j.getId() == jogadorId) {
            saldo += j.getPreco();
            break;
        }
    }
    timeEscalado.removerJogador(jogadorId);
}

void Usuario::escalarTime(const std::vector<int>& jogadoresIds) {
    // Implementar lógica de escalação
}

// Implementação do método abstrato de Pessoa
void Usuario::exibirInfo() const {
    std::cout << "Usuário: " << nome << " (ID: " << id << ")\n";
    std::cout << "Saldo: R$" << saldo << ", Time: " << timeEscalado.getNome() << std::endl;
}