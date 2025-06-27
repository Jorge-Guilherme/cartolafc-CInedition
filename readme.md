# Cartola FC CIn Edition

Simulação de fantasy game inspirada no Cartola FC, desenvolvida em C++ para terminal. O usuário pode comprar jogadores, escalar seu time, participar de rodadas e acompanhar o ranking dos participantes.

## Como rodar o projeto

### Pré-requisitos

- **Compilador C++**
- **make**

### Passos

1. **Clone o repositório e acesse a pasta do projeto:**

   ```sh
   git clone <url-do-repo>
   cd cartolafc-CInedition
   ```
2. **Compile o projeto:**

   ```sh
   make
   ```

   Isso irá gerar o executável `cartola` na raiz do projeto.
3. **Garanta que os arquivos de dados existam:**

   - `data/jogadores.json`
   - `data/usuarios.json`
   - `data/rodadas.json`

   Eles já vêm com exemplos, mas você pode editar conforme desejar.
4. **Execute o programa:**

   ```sh
   ./cartola
   ```

## Estrutura do Projeto

- `src/` — Código-fonte principal (main, lógica de usuário, mercado, rodada, etc)
- `include/` — Headers das classes principais (Jogador, Usuario, TimeEscalado, Mercado, etc)
- `data/` — Arquivos JSON com dados de jogadores, usuários e rodadas
- `Makefile` — Script para compilar facilmente

## Conceitos e Entidades

### Usuário

- Representa o participante do fantasy.
- Possui um nome, saldo (dinheiro virtual) e um time escalado.
- Pode comprar/vender jogadores e escalar titulares.

### Jogador

- Representa um atleta disponível no mercado.
- Possui atributos como nome, posição, preço, gols, assistências, cartões e pontuação.
- Os dados são carregados de `data/jogadores.json`.

### Time Escalado

- Cada usuário tem um time, composto por jogadores comprados e titulares escalados.
- O usuário pode escalar até 11 titulares por rodada.
- A pontuação do time é calculada com base no desempenho dos titulares.

### Mercado

- Lista todos os jogadores disponíveis para compra.
- Permite ao usuário comprar/vender jogadores, respeitando o saldo disponível.

### Rodada

- Simula uma rodada do campeonato.
- Atualiza a pontuação dos jogadores e dos times dos usuários.

### Ranking

- Exibe a classificação dos usuários com base na pontuação total dos seus times.

## Como funciona o fluxo do jogo

1. **Login/Cadastro:** O usuário faz login ou cria uma conta.
2. **Mercado:** Compra e vende jogadores para montar seu elenco.
3. **Escalação:** Seleciona até 11 titulares dentre os jogadores comprados.
4. **Iniciar Rodada:** Calcula a pontuação dos titulares com base nos dados da rodada.
5. **Ranking:** Visualiza a classificação geral dos usuários.
6. **Logout/Sair:** Encerra a sessão ou o programa.

## Observações

- Os dados dos usuários e times são salvos em `data/usuarios.json` após cada operação relevante.
- Caso queiram testar com jogadores/rodadas novas, basta editar os arquivos em `data/.json`

## Equipe

1. Jorge Guilherme `<jglvc>`
2. Vinicius França `<vfs2>`
3. Pedro Francisco `<pfcc>`
4. Hugo Kauan `<hklc>`
