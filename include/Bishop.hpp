#pragma once

#include "Piece.hpp"

class Bishop: public Piece{
    public:
        Bishop(Coordinates initial_coords, Color color, Board* board);
        bool validateMove(Coordinates final_coordinates) const;
        char getPieceChar() const;
};