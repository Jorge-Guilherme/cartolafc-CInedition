#ifndef PESSOA_H
#define PESSOA_H

#include <string>

// Classe abstrata base para Usuario e Jogador
class Pessoa {
protected:
    int id;
    std::string nome;
public:
    Pessoa(int id, const std::string& nome) : id(id), nome(nome) {}
    virtual ~Pessoa() = default;

    int getId() const { return id; }
    std::string getNome() const { return nome; }
    void setNome(const std::string& n) { nome = n; }

    // Método virtual puro (classe abstrata)
    virtual void exibirInfo() const = 0;
};

#endif 