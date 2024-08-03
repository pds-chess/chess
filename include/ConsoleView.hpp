#pragma once

#include "Match.hpp"
#include <string>

class Console
{
private:
    void createNewGame(std::string playerA, std::string playerB);

    void printBoard();
    void printGameActions(Match& match);
    void printGameEnd();

    void printMatchHistory();
    void printMatch(int matchId);

    // Novos métodos para propor, aceitar e rejeitar empate
    void handleDraw(Match& match);
    void showCapturedPieces(Match& match);
    void movePiece(Match& match);

public:
    // Construtor padrão que inicia o jogo no console.
    Console();
    
    // Primeira função chamada, imprime o menu com as opções de criar novo jogo e ver histórico.
    void printMenu();
    ~Console();
};
