// Usei std::string para representar jogadores pois a classe Jogador ainda não foi definida.
//Incluir Header Jogador quando classe Jogador for definida.

#ifndef TIME_ESCALADO_H
#define TIME_ESCALADO_H

#include <string>
#include <vector>

// Classe do Time escalado
class TimeEscalado {
private:
    std::string nomeTime;
    std::vector<std::string> jogadores;
    std::string tecnico;
    std::string formacao;
    double saldo;
    double valorTime;
    std::string capitao;

public:
    // Construtor padrão
    TimeEscalado();

    // Métodos de acesso (getters)
    std::string getNomeTime() const;
    std::vector<std::string> getJogadores() const;
    std::string getTecnico() const;
    std::string getFormacao() const;
    double getSaldo() const;
    double getValorTime() const;
    std::string getCapitao() const;

    // Métodos de modificação (setters)
    void setNomeTime(const std::string& nome);
    void setTecnico(const std::string& tecnico);
    void setFormacao(const std::string& formacao);
    void setSaldo(double saldo);
    void setValorTime(double valor);
    void setCapitao(const std::string& capitao);

    // Métodos para manipular jogadores
    void adicionarJogador(const std::string& jogador);
    void removerJogador(const std::string& jogador);

    // Exibe as informações do time
    void exibirTime() const;
};

#endif 