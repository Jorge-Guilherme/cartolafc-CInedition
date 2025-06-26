#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include "timeescalado.h"

class Usuario {
public:
    int id;
    std::string nome;
    double saldo;
    TimeEscalado timeEscalado;

    Usuario();
    Usuario(int id, const std::string& nome, double saldo, const TimeEscalado& timeEscalado);
    void comprarJogador(const Jogador& jogador);
    void venderJogador(int jogadorId);
    void escalarTime(const std::vector<int>& jogadoresIds);
};

#endif