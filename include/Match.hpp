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
    int game_id_;
    void endTurn();
    bool isCheck() const;
    bool isDraw() const;
    void movePiece(Piece* target_piece, const Coordinates& final_coords);
    void promotePawn(Piece* pawn);
    void updatePlayers();

    // Atributos para proposta de empate
    bool drawProposed;
    std::string proposingPlayer;

    // Método para finalizar o jogo com empate
    void draw();

    // Lista de movimentos
    std::list<std::string> moves_;
    //History history_;

    // Método para registrar um movimento
    void registerMove(Piece* target_piece, Coordinates final_coords);

public:
    Match(std::string playerW, std::string playerB);
    void startGame(std::string playerW, std::string playerB); // Inicia um novo jogo.
    std::string startTurn();
    void movePiece(int row_start, int col_start, int row_end, int col_end); // Move a peça e retorna o estado do tabuleiro após o movimento.

    // Métodos para gerenciamento de empate
    void proposeDraw(const std::string& player);
    void confirmDraw(const std::string& player);

    // Método para desistência
    void resign();
};
