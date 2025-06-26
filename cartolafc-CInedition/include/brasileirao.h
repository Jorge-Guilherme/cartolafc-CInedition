#ifndef BRASILEIRAO_H
#define BRASILEIRAO_H

#include <string>
#include <vector>
#include "partida.h"

class Brasileirao {
private:
    std::vector<Partida> partidas; // Lista de partidas do campeonato

public:
    // Adiciona uma nova partida ao campeonato
    void adicionarPartida(const Partida& partida);

    // Retorna uma string com a classificação atual (implementação futura)
    std::string getClassificacao() const;
};

#endif
