CXX=g++
CXXFLAGS=-Iinclude -std=c++17
SRC=src/main.cpp src/jogador.cpp src/timeescalado.cpp src/usuario.cpp src/mercado.cpp src/rodada.cpp src/utils.cpp
OUT=cartola

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)