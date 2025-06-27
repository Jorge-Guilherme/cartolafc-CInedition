#include "jogador.h"
#include <json.hpp>
#include <iostream>

// Construtor padrão
Jogador::Jogador() : Pessoa(0, ""), posicao(""), preco(0), gols(0), assistencias(0), cartoes_amarelos(0), cartoes_vermelhos(0), pontuacao(0) {}

// Construtor parametrizado
Jogador::Jogador(int id, const std::string& nome, const std::string& posicao, double preco)
    : Pessoa(id, nome), posicao(posicao), preco(preco), gols(0), assistencias(0), cartoes_amarelos(0), cartoes_vermelhos(0), pontuacao(0) {}

void Jogador::atualizarEstatisticas(int gols, int assistencias, int amarelos, int vermelhos, double pontuacao) {
    this->gols = gols;
    this->assistencias = assistencias;
    this->cartoes_amarelos = amarelos;
    this->cartoes_vermelhos = vermelhos;
    this->pontuacao = pontuacao;
}

// Implementação do método abstrato de Pessoa
void Jogador::exibirInfo() const {
    std::cout << "Jogador: " << nome << " (ID: " << id << ")\n";
    std::cout << "Posição: " << posicao << ", Preço: R$" << preco << ", Pontuação: " << pontuacao << std::endl;
}