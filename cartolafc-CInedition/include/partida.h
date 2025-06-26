#ifndef PARTIDA_H
#define PARTIDA_H

#include <string>
#include <vector>

class Partida {
private:
    int id;                                   // Identificador da partida
    std::string timeCasa;                     // Nome do time mandante
    std::string timeFora;                     // Nome do time visitante
    std::vector<std::string> titularesCasa;   // Titulares do time mandante
    std::vector<std::string> reservasCasa;    // Reservas do time mandante
    std::vector<std::string> titularesFora;   // Titulares do time visitante
    std::vector<std::string> reservasFora;    // Reservas do time visitante
    std::string dataHora;                     // Data e hora da partida
    int rodada;                               // Número da rodada
    int placarCasa;                           // Placar do time mandante
    int placarFora;                           // Placar do time visitante
    std::vector<std::string> eventos;         // Lista de eventos ocorridos na partida

public:

    // Construtor
    Partida(int id, const std::string& timeCasa, const std::string& timeFora, const std::string& dataHora, int rodada);

    // Métodos para adicionar jogadores titulares e reservas
    void adicionarTitularCasa(const std::string& jogador);
    void adicionarReservaCasa(const std::string& jogador);
    void adicionarTitularFora(const std::string& jogador);
    void adicionarReservaFora(const std::string& jogador); 

    // Registra um novo evento na partida
    void registrarEvento(const std::string& descricaoEvento);

    // Registra uma substituição 
    void registrarSubstituicaoCasa(const std::string& jogadorSai, const std::string& jogadorEntra);
    void registrarSubstituicaoFora(const std::string& jogadorSai, const std::string& jogadorEntra);

    // Atualiza as estatísticas da partida 
    void atualizarEstatisticas();

    // Retorna uma string com os detalhes da partida
    std::string getDetalhes() const;
};

#endif 