#pragma once

#include "Piece.hpp"

class Bishop: public Piece{
    public:
        Bishop(const Coordinates& initial_coords, Color color, const Board& board);
        bool validateMove(const Coordinates& final_coordinates) const override;
        PieceType getType() const override;
    protected:
        char getPieceChar() const override;
};