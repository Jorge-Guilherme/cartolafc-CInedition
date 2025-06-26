#include "utils.h"
#include <fstream>
#include <json.hpp>

using json = nlohmann::json;

namespace Utils {

std::vector<Jogador> carregarJogadores(const std::string& filename) {
    std::vector<Jogador> jogadores;
    std::ifstream file(filename);
    if (!file.is_open()) return jogadores;
    json data;
    file >> data;
    for (const auto& item : data) {
        Jogador j;
        j.id = item["id"];
        j.nome = item["nome"];
        j.posicao = item["posicao"];
        j.preco = item["preco"];
        j.gols = item["gols"];
        j.assistencias = item["assistencias"];
        j.cartoes_amarelos = item["cartoes_amarelos"];
        j.cartoes_vermelhos = item["cartoes_vermelhos"];
        j.pontuacao = item["pontuacao"];
        jogadores.push_back(j);
    }
    return jogadores;
}

// As funções abaixo são exemplos, você pode expandir conforme sua necessidade

void salvarUsuarios(const std::string& filename, const std::vector<Usuario>& usuarios) {
    // Exemplo: salvar apenas nome e saldo
    json data = json::array();
    for (const auto& u : usuarios) {
        data.push_back({
            {"id", u.id},
            {"nome", u.nome},
            {"saldo", u.saldo}
            // Adicione mais campos conforme necessário
        });
    }
    std::ofstream file(filename);
    file << data.dump(4);
}

std::vector<Usuario> carregarUsuarios(const std::string& filename) {
    std::vector<Usuario> usuarios;
    std::ifstream file(filename);
    if (!file.is_open()) return usuarios;
    json data;
    file >> data;
    for (const auto& item : data) {
        Usuario u;
        u.id = item["id"];
        u.nome = item["nome"];
        u.saldo = item["saldo"];
        // Adicione mais campos conforme necessário
        usuarios.push_back(u);
    }
    return usuarios;
}

void salvarRodadas(const std::string& filename, const std::vector<Rodada>& rodadas) {
    // Exemplo: salvar apenas número da rodada
    json data = json::array();
    for (const auto& r : rodadas) {
        data.push_back({{"numero", r.numero}});
    }
    std::ofstream file(filename);
    file << data.dump(4);
}

std::vector<Rodada> carregarRodadas(const std::string& filename) {
    std::vector<Rodada> rodadas;
    std::ifstream file(filename);
    if (!file.is_open()) return rodadas;
    json data;
    file >> data;
    for (const auto& item : data) {
        Rodada r;
        r.numero = item["numero"];
        rodadas.push_back(r);
    }
    return rodadas;
}

}