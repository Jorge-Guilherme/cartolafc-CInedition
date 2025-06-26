#ifndef JOGADOR_H
#define JOGADOR_H

#include <string>


class Jogador {
protected:
    std::string nome;
    std::string time;
    int pontuacao;
public:
    Jogador(std::string nome_jogador, std::string time_jogador);
    ~Jogador();
    std::string get_posicao() const;
    std::string get_nome() const;
    std::string get_time() const;
    int get_pontuacao() const;
    void set_time(std::string novo_time);
    void set_pontuacao()const;

};

#endif