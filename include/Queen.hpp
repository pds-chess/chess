#pragma once

#include "Piece.hpp"

class Queen: public Piece{
    public:
        Queen(const Coordinates& initial_coords, Color color, const  Board& board);
        ~Queen();
        bool validateMove(const Coordinates& final_coordinates) const override;
        PieceType getType() const override;
    protected:
        char getPieceChar() const override;
};