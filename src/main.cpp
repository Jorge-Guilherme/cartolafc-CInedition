#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "usuario.h"
#include "mercado.h"
#include "rodada.h"
#include "utils.h"
#include <json.hpp>

void exibirMenuLogin() {
    std::cout << "\n==== Cartola FC CIn Edition ====" << std::endl;
    std::cout << "1. Login/Cadastro" << std::endl;
    std::cout << "0. Sair" << std::endl;
    std::cout << "Escolha uma opção: ";
}

void exibirMenuUsuario(const Usuario& usuario) {
    std::cout << "\n==== Cartola FC CIn Edition ====" << std::endl;
    std::cout << "Usuário: " << usuario.getNome() << " | Saldo: " << usuario.getSaldo() << std::endl;
    std::cout << "Time: " << usuario.getTimeEscalado().getNome() << std::endl;
    std::cout << "Pontuação total: " << usuario.getTimeEscalado().getPontuacaoTotal() << std::endl;
    std::cout << "1. Mercado de Jogadores" << std::endl;
    std::cout << "2. Escalar Time" << std::endl;
    std::cout << "3. Iniciar Rodada" << std::endl;
    std::cout << "4. Exibir Ranking" << std::endl;
    std::cout << "5. Logout" << std::endl;
    std::cout << "0. Sair" << std::endl;
    std::cout << "Escolha uma opção: ";
}

void menuMercado(Mercado& mercado, Usuario& usuario) {
    int escolha;
    do {
        std::cout << "\nSeu saldo: " << usuario.getSaldo() << std::endl;
        std::cout << "Jogadores disponíveis para compra:" << std::endl;
        std::vector<int> idsComprados;
        for (const auto& j : usuario.getTimeEscalado().getComprados()) {
            idsComprados.push_back(j.getId());
        }
        bool algumDisponivel = false;
        for (const auto& j : mercado.jogadoresDisponiveis) {
            if (std::find(idsComprados.begin(), idsComprados.end(), j.getId()) == idsComprados.end()) {
                std::cout << j.getId() << "\t" << j.getNome() << "\t" << j.getPosicao() << "\tR$" << j.getPreco() << std::endl;
                algumDisponivel = true;
            }
        }
        if (!algumDisponivel) {
            std::cout << "Nenhum jogador disponível para compra." << std::endl;
        }
        std::cout << "1. Comprar jogador\n2. Vender jogador\n0. Voltar\nEscolha: ";
        std::cin >> escolha;
        if (escolha == 1) {
            int id;
            std::cout << "Digite o ID do jogador para comprar: ";
            std::cin >> id;
            if (std::find(idsComprados.begin(), idsComprados.end(), id) != idsComprados.end()) {
                std::cout << "Você já possui esse jogador." << std::endl;
            } else {
                std::vector<Jogador> dummyVec; // não será usado
                if (mercado.comprarJogador(id, usuario.saldoRef(), dummyVec)) {
                    // Encontre o jogador no mercado
                    auto it = std::find_if(mercado.jogadoresDisponiveis.begin(), mercado.jogadoresDisponiveis.end(),
                                           [id](const Jogador& j){ return j.getId() == id; });
                    if (it != mercado.jogadoresDisponiveis.end()) {
                        usuario.getTimeEscalado().adicionarJogador(*it);
                    }
                    std::cout << "Jogador comprado!" << std::endl;
                } else {
                    std::cout << "Não foi possível comprar (saldo insuficiente ou jogador não existe)." << std::endl;
                }
            }
        } else if (escolha == 2) {
            int id;
            std::cout << "Digite o ID do jogador para vender: ";
            std::cin >> id;
            usuario.getTimeEscalado().removerJogador(id); // Remove de comprados e titulares
            for (const auto& j : mercado.jogadoresDisponiveis) {
                if (j.getId() == id) {
                    double novoSaldo = usuario.getSaldo() + j.getPreco();
                    usuario.setSaldo(novoSaldo);
                    std::cout << "Jogador vendido!" << std::endl;
                    goto fim_venda;
                }
            }
            std::cout << "Jogador não está no seu time." << std::endl;
            fim_venda:;
        }
    } while (escolha != 0);
}

void menuEscalacao(Usuario& usuario) {
    auto& todos = usuario.getTimeEscalado().getComprados();
    if (todos.empty()) {
        std::cout << "\nVocê não possui jogadores comprados para escalar." << std::endl;
        return;
    }
    std::cout << "\nSeus jogadores comprados:" << std::endl;
    for (const auto& j : todos) {
        std::cout << j.getId() << ": " << j.getNome() << " (" << j.getPosicao() << ") - R$" << j.getPreco() << "\n";
    }
    std::cout << "Digite os IDs dos jogadores que deseja escalar como titulares (até 11, separados por espaço): ";
    std::vector<int> ids;
    int id;
    for (int i = 0; i < 11 && std::cin >> id; ++i) {
        ids.push_back(id);
        if (std::cin.peek() == '\n') break;
    }
    std::cin.ignore(10000, '\n');
    std::vector<Jogador> titulares;
    for (int tid : ids) {
        auto it = std::find_if(todos.begin(), todos.end(), [tid](const Jogador& j){ return j.getId() == tid; });
        if (it != todos.end()) {
            titulares.push_back(*it);
        }
    }
    usuario.getTimeEscalado().getTitulares() = titulares;
    std::cout << "\nTitulares escalados:" << std::endl;
    for (const auto& j : usuario.getTimeEscalado().getTitulares()) {
        std::cout << j.getId() << ": " << j.getNome() << " (" << j.getPosicao() << ")\n";
    }
}

void menuIniciarRodada(std::vector<Jogador>& jogadores, Usuario& usuario) {
    for (auto& meuJogador : usuario.getTimeEscalado().getTitulares()) {
        for (const auto& atualizado : jogadores) {
            if (meuJogador.getId() == atualizado.getId()) {
                meuJogador.setPontuacao(atualizado.getPontuacao());
            }
        }
    }
    usuario.getTimeEscalado().calcularPontuacao();
    std::cout << "\nPontuação do seu time nesta rodada: " << usuario.getTimeEscalado().getPontuacaoTotal() << std::endl;
}

void menuRanking(const std::vector<Usuario>& usuarios) {
    std::vector<std::pair<std::string, double>> ranking;
    for (const auto& u : usuarios) {
        ranking.push_back({u.getNome(), u.getTimeEscalado().getPontuacaoTotal()});
    }
    std::sort(ranking.begin(), ranking.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });
    std::cout << "\n==== Ranking dos Times ====" << std::endl;
    int pos = 1;
    for (const auto& r : ranking) {
        std::cout << pos++ << ". " << r.first << " - " << r.second << " pontos" << std::endl;
    }
}

int main() {
    std::vector<Usuario> usuarios = Utils::carregarUsuarios("data/usuarios.json");
    std::vector<Jogador> jogadores = Utils::carregarJogadores("data/jogadores.json");
    std::vector<Rodada> rodadas = Utils::carregarRodadas("data/rodadas.json");
    Mercado mercado;
    mercado.jogadoresDisponiveis = jogadores;

    int usuarioLogadoIdx = -1;
    int opcao = -1;
    while (true) {
        if (usuarioLogadoIdx == -1) {
            exibirMenuLogin();
            std::cin >> opcao;
            std::cin.ignore();
            if (opcao == 1) {
                std::cout << "Digite seu nome de usuário: ";
                std::string nome;
                std::getline(std::cin, nome);
                bool encontrado = false;
                for (size_t i = 0; i < usuarios.size(); ++i) {
                    if (usuarios[i].getNome() == nome) {
                        usuarioLogadoIdx = static_cast<int>(i);
                        encontrado = true;
                        std::cout << "Bem-vindo de volta, " << nome << "!" << std::endl;
                        break;
                    }
                }
                if (!encontrado) {
                    Usuario novo(usuarios.size() + 1, nome, 100.0, TimeEscalado(usuarios.size() + 1, nome + " FC"));
                    usuarios.push_back(novo);
                    usuarioLogadoIdx = static_cast<int>(usuarios.size() - 1);
                    std::cout << "Usuário cadastrado com sucesso! Bem-vindo, " << nome << "!" << std::endl;
                    Utils::salvarUsuarios("data/usuarios.json", usuarios);
                }
            } else if (opcao == 0) {
                std::cout << "Saindo..." << std::endl;
                break;
            } else {
                std::cout << "Opção inválida!" << std::endl;
            }
        } else {
            exibirMenuUsuario(usuarios[usuarioLogadoIdx]);
            std::cin >> opcao;
            std::cin.ignore();
            if (opcao == 1) {
                menuMercado(mercado, usuarios[usuarioLogadoIdx]);
                Utils::salvarUsuarios("data/usuarios.json", usuarios);
            } else if (opcao == 2) {
                menuEscalacao(usuarios[usuarioLogadoIdx]);
            } else if (opcao == 3) {
                menuIniciarRodada(jogadores, usuarios[usuarioLogadoIdx]);
                Utils::salvarUsuarios("data/usuarios.json", usuarios);
            } else if (opcao == 4) {
                menuRanking(usuarios);
            } else if (opcao == 5) {
                usuarioLogadoIdx = -1;
                std::cout << "Logout realizado." << std::endl;
            } else if (opcao == 0) {
                std::cout << "Saindo..." << std::endl;
                break;
            } else {
                std::cout << "Opção inválida!" << std::endl;
            }
        }
    }
    return 0;
} 