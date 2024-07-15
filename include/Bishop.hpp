#pragma once

#include "Piece.hpp"

class Bishop: public Piece{
    public:
        Bishop(Coordinates initial_coords, Color color, Board* board);
        virtual bool validateMove(Coordinates final_coordinates) const;
        virtual char getPieceChar() const;
};