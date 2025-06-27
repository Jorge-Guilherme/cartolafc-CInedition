// include/timeescalado.h
#ifndef TIMEESCALADO_H
#define TIMEESCALADO_H

#include <string>
#include <vector>
#include "jogador.h"

class TimeEscalado {
private:
    int id;
    std::string nome;
    std::vector<Jogador> comprados; // jogadores comprados
    std::vector<Jogador> titulares; // titulares escalados
    double pontuacaoTotal;
public:
    TimeEscalado();
    TimeEscalado(int id, const std::string& nome);
    void adicionarJogador(const Jogador& jogador);
    void removerJogador(int jogadorId);
    void calcularPontuacao();
    // Gets
    std::string getNome() const { return nome; }
    double getPontuacaoTotal() const { return pontuacaoTotal; }
    std::vector<Jogador>& getComprados() { return comprados; }
    const std::vector<Jogador>& getComprados() const { return comprados; }
    std::vector<Jogador>& getTitulares() { return titulares; }
    const std::vector<Jogador>& getTitulares() const { return titulares; }
};

#endif