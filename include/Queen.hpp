#pragma once

#include "Piece.hpp"

class Queen: public Piece{
    public:
        Queen(Coordinates initial_coords, Color color, Board* board);
        bool validateMove(Coordinates final_coordinates) const;
        char getPieceChar() const;
};