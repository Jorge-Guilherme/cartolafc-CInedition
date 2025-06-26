#include "jogador.h"
#include <json.hpp>

Jogador::Jogador() : id(0), preco(0), gols(0), assistencias(0), cartoes_amarelos(0), cartoes_vermelhos(0), pontuacao(0) {}

Jogador::Jogador(int id, const std::string& nome, const std::string& posicao, double preco)
    : id(id), nome(nome), posicao(posicao), preco(preco), gols(0), assistencias(0), cartoes_amarelos(0), cartoes_vermelhos(0), pontuacao(0) {}

void Jogador::atualizarEstatisticas(int gols, int assistencias, int amarelos, int vermelhos, double pontuacao) {
    this->gols = gols;
    this->assistencias = assistencias;
    this->cartoes_amarelos = amarelos;
    this->cartoes_vermelhos = vermelhos;
    this->pontuacao = pontuacao;
}