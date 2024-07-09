#pragma once

#include "Board.hpp"
#include "History.hpp"
#include "Player.hpp"
#include "GameState.hpp"

#include <string>

class Match{
    private:
        Board board;
        Player playerW;
        Player playerB;

    public:
        Match(std::string playerW, std::string playerB); //Define o nome dos jogares e inicia o jogo.
        void startGame(); //Inicia o jogo.
        std::string movePiece(int row_start, int col_start, int row_end, int col_end); //Move a peça e retorna o estado do tabuleiro após o movimento.
        bool getGameOver(); //Retorna true se o jogo finalizou.
        void setGameState(Gamestate state);
};