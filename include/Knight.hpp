#pragma once

#include "Piece.hpp"

class Knight: public Piece{
    public:
        Knight(const Coordinates& initial_coords, Color color, const Board& board);
        virtual bool validateMove(const Coordinates& final_coordinates) const;
        virtual char getPieceChar() const;
};