#ifndef JOGADOR_H
#define JOGADOR_H

#include "pessoa.h"
#include <string>

class Jogador : public Pessoa {
private:
    std::string posicao;
    double preco;
    int gols;
    int assistencias;
    int cartoes_amarelos;
    int cartoes_vermelhos;
    double pontuacao;
public:
    Jogador();
    Jogador(int id, const std::string& nome, const std::string& posicao, double preco);

    // Gets/Sets
    std::string getPosicao() const { return posicao; }
    double getPreco() const { return preco; }
    int getGols() const { return gols; }
    int getAssistencias() const { return assistencias; }
    int getCartoesAmarelos() const { return cartoes_amarelos; }
    int getCartoesVermelhos() const { return cartoes_vermelhos; }
    double getPontuacao() const { return pontuacao; }

    void setPosicao(const std::string& p) { posicao = p; }
    void setPreco(double pr) { preco = pr; }
    void setGols(int g) { gols = g; }
    void setAssistencias(int a) { assistencias = a; }
    void setCartoesAmarelos(int ca) { cartoes_amarelos = ca; }
    void setCartoesVermelhos(int cv) { cartoes_vermelhos = cv; }
    void setPontuacao(double p) { pontuacao = p; }

    void atualizarEstatisticas(int gols, int assistencias, int amarelos, int vermelhos, double pontuacao);

    // Implementação do método abstrato
    void exibirInfo() const override;
};

#endif