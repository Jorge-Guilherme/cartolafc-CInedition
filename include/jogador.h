#ifndef JOGADOR_H
#define JOGADOR_H

#include <string>

class Jogador {
public:
    int id;
    std::string nome;
    std::string posicao;
    double preco;
    int gols;
    int assistencias;
    int cartoes_amarelos;
    int cartoes_vermelhos;
    double pontuacao;

    Jogador();
    Jogador(int id, const std::string& nome, const std::string& posicao, double preco);
    void atualizarEstatisticas(int gols, int assistencias, int amarelos, int vermelhos, double pontuacao);
};

#endif