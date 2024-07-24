#pragma once

#include "GameController.hpp"

#include <string>

class Console
{
private:
    // Primeira função chamada, imprime o menu com as opções de criar novo jogo e ver histórico.
    void printMenu();

    void printNewGame();
    void savePlayersName();

    void printBoard();
    void printGameActions();
    void printGameEnd();

    void printMatchHistory();
    void printMatch(int matchId);
 // Novos métodos para propor, aceitar e rejeitar empate
    void proposeDraw();
    void handleDrawResponse();

public:
    // Construtor padrão que inicia o jogo no console.
    Console();

    ~Console();
};
