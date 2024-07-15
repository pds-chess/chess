#pragma once

#include "Piece.hpp"

class Knight: public Piece{
    public:
        Knight(Coordinates initial_coords, Color color, Board* board);
        virtual bool validateMove(Coordinates final_coordinates) const;
        virtual char getPieceChar() const;
};