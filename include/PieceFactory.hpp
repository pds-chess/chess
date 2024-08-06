#pragma once

#include "Piece.hpp"
#include "PieceType.hpp"

class PieceFactory{
    private:
    public:
        PieceFactory();
        Piece* createPiece(const Coordinates& coords, Color color, const Board& board, PieceType type);
        Piece* createPiece(Piece* piece, const Board& board);
};