#pragma once

#include "Board.hpp"
#include "History.hpp"
#include "Player.hpp"
#include "GameState.hpp"
#include "Color.hpp"

#include <string>

class Match{
    private:
        Board board_;
        Player player_W_;
        Player player_B_;
        Player* current_turn_;
        Gamestate game_state_;
        void endTurn();
        bool isCheck() const;
        bool isDraw() const;
        void movePiece(Piece* target_piece, Coordinates final_coords);
        void promotePawn(Piece* pawn, int chosen_piece);
        void updatePlayers();
    public:
        Match(std::string playerW, std::string playerB);
        void startGame(std::string playerW, std::string playerB); //Inicia um novo jogo.
        std::string startTurn();
        void movePiece(int row_start, int col_start, int row_end, int col_end); //Move a peça e retorna o estado do tabuleiro após o movimento.
};