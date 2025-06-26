#ifndef POSICOES_H
#define POSICOES_H
#include "JOGADOR.H"


class Goleiro : public Jogador {
public:
    Goleiro(std::string nome_goleiro, std::string time_goleiro);
    std::string get_posicao() const;
};

class Atacante : public Jogador {
public:
    Atacante(std::string nome_atacante, std::string time_atacante);
    std::string get_posicao() const;
};

class Zagueiro : public Jogador {
public:
    Zagueiro(std::string nome_zagueiro, std::string time_zagueiro);
    std::string get_posicao() const;
};

class MeioCampista : public Jogador {
public:
    MeioCampista(std::string nome_meio_campista, std::string time_meio_campista);
    std::string get_posicao() const;
};
#endif