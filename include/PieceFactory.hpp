#pragma once

#include "Piece.hpp"
#include "PieceType.hpp"

class PieceFactory{
    private:
    public:
        /**
          * @brief Default Constructor. 
          */
        PieceFactory();

        /**
          * @brief Create a new piece in the specified position.
          * @param coords.
          * @param color.
          * @param board.
          * @param type Type of the piece.
          * @return Returns a list of pieces.
          */
        Piece* createPiece(const Coordinates& coords, Color color, const Board& board, PieceType type);

        /**
          * @brief Create a copy of the piece.
          * @param piece. 
          * @param board.
          * @return Returns a list of pieces.
          */
        Piece* createPiece(Piece* piece, const Board& board);
};