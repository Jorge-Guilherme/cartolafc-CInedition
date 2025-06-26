#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include "jogador.h"
#include "usuario.h"
#include "rodada.h"

namespace Utils {
    std::vector<Jogador> carregarJogadores(const std::string& filename);
    void salvarUsuarios(const std::string& filename, const std::vector<Usuario>& usuarios);
    std::vector<Usuario> carregarUsuarios(const std::string& filename);
    void salvarRodadas(const std::string& filename, const std::vector<Rodada>& rodadas);
    std::vector<Rodada> carregarRodadas(const std::string& filename);
}

#endif 