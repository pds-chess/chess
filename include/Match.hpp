#pragma once

#include "Board.hpp"
#include "History.hpp"
#include "Player.hpp"
#include "GameState.hpp"
#include "Color.hpp"
#include "King.hpp"
#include "Pawn.hpp"
#include <string>
#include <list>

class Match {
private:
    Board board_;
    Player player_W_;
    Player player_B_;
    Player* current_turn_;
    Gamestate game_state_;
        int game_id_ = 0;
    void endTurn();
    bool isCheck() const;
    bool isDraw() const;
    void movePiece(Piece* target_piece, const Coordinates& final_coords);
    void promotePawn(Piece* pawn);
    void updatePlayers();

    void startGame(); // Inicia um novo jogo.

    // Lista de movimentos
    std::list<Move> moves_;
    // History history_;

    // Método para registrar um movimento
    void registerMove(Piece* target_piece, Coordinates final_coords);

public:
    Match(std::string playerW, std::string playerB);
    std::string boardToString() const;
    void movePiece(int row_start, int col_start, int row_end, int col_end); // Move a peça e retorna o estado do tabuleiro após o movimento.
    Gamestate getGameState();
    std::string getCurrentPlayerName() const;
     // Método para finalizar o jogo com empate
    void draw();

    // Método para desistência
    void resign();
    void showCapturedPieces();

};
