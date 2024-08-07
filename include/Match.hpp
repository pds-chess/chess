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
    bool isDraw() const;
    bool simulateMove(const Coordinates& coord_start, const Coordinates& coord_end) const;
    void updatePlayers();

    void startGame(); // Inicia um novo jogo.

    // Lista de movimentos
    std::list<Move> moves_;
    // History history_;

    // Método para registrar um movimento
    void registerMove(Piece* target_piece, Coordinates final_coords);
    Piece* getPieceInGame(int row, int col) const;

public:
    /**
      * @brief Constructor.
      * @param playerW Player of the White pieces.
      * @param playerB Player of the Black pieces.
      */
    Match(std::string playerW, std::string playerB);

    /**
      * @brief Transform the current state of the board into a string.
      * @return Returns string
      */
    std::string boardToString() const;

    /**
      * @brief Move Piece.
      * @param row_start Start row in the first move.
      * @param col_start Start column in the first move.
      * @param row_end End row in the last move.
      * @param col_end End column in the last move.
      */
    void movePiece(int row_start, int col_start, int row_end, int col_end);

    /**
      * @brief Move the piece and return the state of the board after the move.
      * @return Returns Gamestate      
      */
    Gamestate getGameState();

    /**
      * @brief Get Current Player Name.
      */
    std::string getCurrentPlayerName() const;

    /**
      * @brief Promote the pawn.
      * @param row_end End row in the last move.
      * @param col_end End column in the last move.    
      * @return Returns true (promoted pawn) or false (unpromoted pawn). 
      */          
    bool isPromote(int row_end, int col_end) const;

    /**
      * @brief Promote the pawn.          
      * @param row.
      * @param col.
      * @param type Option to choose.
      */
    void promotePawn(int row, int col, PieceType type);
     
    /**
      * @brief End the game with a draw, as there aren't moves.
      */
    void draw();
    
    /**
      * @brief End the game with forfeit.
      */
    void resign();

    /**
      * @brief Print all opposing pieces that have been captured.
      * @return Returns string      
      */
    std::string showCapturedPieces();

};
