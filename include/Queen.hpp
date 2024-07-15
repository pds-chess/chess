#pragma once

#include "Piece.hpp"

class Queen: public Piece{
    public:
        Queen(Coordinates initial_coords, Color color, Board* board);
        virtual bool validateMove(Coordinates final_coordinates) const;
        virtual char getPieceChar() const;
};