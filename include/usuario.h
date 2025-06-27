#ifndef USUARIO_H
#define USUARIO_H

#include "pessoa.h"
#include "timeescalado.h"
#include <string>

class Usuario : public Pessoa {
private:
    double saldo;
    TimeEscalado timeEscalado;
public:
    Usuario();
    Usuario(int id, const std::string& nome, double saldo, const TimeEscalado& timeEscalado);

    // Gets/Sets
    double getSaldo() const { return saldo; }
    void setSaldo(double s) { saldo = s; }
    double& saldoRef() { return saldo; }
    TimeEscalado& getTimeEscalado() { return timeEscalado; }
    const TimeEscalado& getTimeEscalado() const { return timeEscalado; }
    void setTimeEscalado(const TimeEscalado& t) { timeEscalado = t; }

    void comprarJogador(const Jogador& jogador);
    void venderJogador(int jogadorId);
    void escalarTime(const std::vector<int>& jogadoresIds);

    // Implementação do método abstrato
    void exibirInfo() const override;
};

#endif