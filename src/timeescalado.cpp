#include "timeescalado.h"
#include <json.hpp>
#include <algorithm>

TimeEscalado::TimeEscalado() : id(0), pontuacaoTotal(0) {}

TimeEscalado::TimeEscalado(int id, const std::string& nome) : id(id), nome(nome), pontuacaoTotal(0) {}

void TimeEscalado::adicionarJogador(const Jogador& jogador) {
    auto it = std::find_if(comprados.begin(), comprados.end(), [&](const Jogador& j){ return j.id == jogador.id; });
    if (it == comprados.end()) {
        comprados.push_back(jogador);
    }
}

void TimeEscalado::removerJogador(int jogadorId) {
    comprados.erase(
        std::remove_if(comprados.begin(), comprados.end(),
            [jogadorId](const Jogador& j) { return j.id == jogadorId; }),
        comprados.end()
    );
    titulares.erase(
        std::remove_if(titulares.begin(), titulares.end(),
            [jogadorId](const Jogador& j) { return j.id == jogadorId; }),
        titulares.end()
    );
}

void TimeEscalado::calcularPontuacao() {
    pontuacaoTotal = 0;
    for (const auto& j : titulares) {
        pontuacaoTotal += j.pontuacao;
    }
}