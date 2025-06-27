#include "rodada.h"
#include <json.hpp>

Rodada::Rodada() : numero(0) {}
Rodada::Rodada(int numero) : numero(numero) {}

void Rodada::atualizarPontuacoes(std::vector<Usuario>& usuarios, const std::vector<Jogador>& jogadoresAtualizados) {
    for (auto& usuario : usuarios) {
        for (auto& meuJogador : usuario.getTimeEscalado().getTitulares()) {
            for (const auto& atualizado : jogadoresAtualizados) {
                if (meuJogador.getId() == atualizado.getId()) {
                    meuJogador.setPontuacao(atualizado.getPontuacao());
                }
            }
        }
        usuario.getTimeEscalado().calcularPontuacao();
    }
}