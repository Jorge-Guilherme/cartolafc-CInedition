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
    std::cout << "Usuário: " << usuario.nome << " | Saldo: " << usuario.saldo << std::endl;
    std::cout << "Time: " << usuario.timeEscalado.nome << std::endl;
    std::cout << "Pontuação total: " << usuario.timeEscalado.pontuacaoTotal << std::endl;
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
        std::cout << "\nSeu saldo: " << usuario.saldo << std::endl;
        std::cout << "Jogadores disponíveis para compra:" << std::endl;
        std::vector<int> idsComprados;
        for (const auto& j : usuario.timeEscalado.comprados) {
            idsComprados.push_back(j.id);
        }
        bool algumDisponivel = false;
        for (const auto& j : mercado.jogadoresDisponiveis) {
            if (std::find(idsComprados.begin(), idsComprados.end(), j.id) == idsComprados.end()) {
                std::cout << j.id << "\t" << j.nome << "\t" << j.posicao << "\tR$" << j.preco << std::endl;
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
            } else if (mercado.comprarJogador(id, usuario.saldo, usuario.timeEscalado.comprados)) {
                std::cout << "Jogador comprado!" << std::endl;
            } else {
                std::cout << "Não foi possível comprar (saldo insuficiente ou jogador não existe)." << std::endl;
            }
        } else if (escolha == 2) {
            int id;
            std::cout << "Digite o ID do jogador para vender: ";
            std::cin >> id;
            usuario.timeEscalado.removerJogador(id); // Remove de comprados e titulares
            // Só atualiza saldo pelo mercado
            for (const auto& j : mercado.jogadoresDisponiveis) {
                if (j.id == id) {
                    usuario.saldo += j.preco;
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
    std::vector<Jogador> todos = usuario.timeEscalado.comprados;
    if (todos.empty()) {
        std::cout << "\nVocê não possui jogadores comprados para escalar." << std::endl;
        return;
    }
    std::cout << "\nSeus jogadores comprados:" << std::endl;
    for (const auto& j : todos) {
        std::cout << j.id << ": " << j.nome << " (" << j.posicao << ") - R$" << j.preco << "\n";
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
        auto it = std::find_if(todos.begin(), todos.end(), [tid](const Jogador& j){ return j.id == tid; });
        if (it != todos.end()) {
            titulares.push_back(*it);
        }
    }
    usuario.timeEscalado.titulares = titulares;
    std::cout << "\nTitulares escalados:" << std::endl;
    for (const auto& j : usuario.timeEscalado.titulares) {
        std::cout << j.id << ": " << j.nome << " (" << j.posicao << ")\n";
    }
}

void menuIniciarRodada(std::vector<Jogador>& jogadores, Usuario& usuario) {
    for (auto& meuJogador : usuario.timeEscalado.titulares) {
        for (const auto& atualizado : jogadores) {
            if (meuJogador.id == atualizado.id) {
                meuJogador.pontuacao = atualizado.pontuacao;
            }
        }
    }
    usuario.timeEscalado.calcularPontuacao();
    std::cout << "\nPontuação do seu time nesta rodada: " << usuario.timeEscalado.pontuacaoTotal << std::endl;
}

void menuRanking(const std::vector<Usuario>& usuarios) {
    std::vector<std::pair<std::string, double>> ranking;
    for (const auto& u : usuarios) {
        ranking.push_back({u.nome, u.timeEscalado.pontuacaoTotal});
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

    Usuario* usuarioLogado = nullptr;
    int opcao = -1;
    while (true) {
        if (!usuarioLogado) {
            exibirMenuLogin();
            std::cin >> opcao;
            std::cin.ignore();
            if (opcao == 1) {
                std::cout << "Digite seu nome de usuário: ";
                std::string nome;
                std::getline(std::cin, nome);
                bool encontrado = false;
                for (auto& u : usuarios) {
                    if (u.nome == nome) {
                        usuarioLogado = &u;
                        encontrado = true;
                        std::cout << "Bem-vindo de volta, " << nome << "!" << std::endl;
                        break;
                    }
                }
                if (!encontrado) {
                    Usuario novo(usuarios.size() + 1, nome, 100.0, TimeEscalado(usuarios.size() + 1, nome + " FC"));
                    usuarios.push_back(novo);
                    usuarioLogado = &usuarios.back();
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
            exibirMenuUsuario(*usuarioLogado);
            std::cin >> opcao;
            std::cin.ignore();
            if (opcao == 1) {
                menuMercado(mercado, *usuarioLogado);
                Utils::salvarUsuarios("data/usuarios.json", usuarios);
            } else if (opcao == 2) {
                menuEscalacao(*usuarioLogado);
            } else if (opcao == 3) {
                menuIniciarRodada(jogadores, *usuarioLogado);
                Utils::salvarUsuarios("data/usuarios.json", usuarios);
            } else if (opcao == 4) {
                menuRanking(usuarios);
            } else if (opcao == 5) {
                usuarioLogado = nullptr;
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