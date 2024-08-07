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

    /**
      * @brief End turn.
      */
    void endTurn();

    /**
      * @brief Is Draw.
      * @return Returns true (draw) or false (no draw).
      */
    bool isDraw() const;

    /**
      * @brief Simulate Move.
      * @param coord_start Initial coordinate.
      * @param coord_end End coordinate.
      * @return True (valid move) or false (invalid move king in check).
      */
    bool simulateMove(const Coordinates& coord_start, const Coordinates& coord_end) const;

    /**
      * @brief Pieces present on the board.
      */
    void updatePlayers();

    /**
      * @brief Start a new game.
      */
    void startGame();

    // Lista de movimentos
    std::list<Move> moves_;
    // History history_;

    /**
      * @brief Register a movement.
      * @param target_piece.
      * @param final_coords End coordinate.
      */
    void registerMove(Piece* target_piece, Coordinates final_coords);

    /**
      * @brief Get the piece to the specified position on the board.
      * @param row.
      * @param col.
      * @return A pointer to the Piece object
      */
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
      * @return string
      */
    std::string boardToString() const;

    /**
      * @brief Move Piece.
      * @param row_start Initial row in the first move.
      * @param col_start Initial column in the first move.
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
      * @return True (promoted pawn) or false (unpromoted pawn). 
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
      * @return String      
      */
    std::string showCapturedPieces();
};