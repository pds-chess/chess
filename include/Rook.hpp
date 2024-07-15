#pragma once

#include "Piece.hpp"

class Rook: public Piece{
    private:
        bool moved_;
    public:
        Rook(Coordinates initial_coords, Color color, Board* board);
        virtual bool validateMove(Coordinates final_coordinates) const;
        bool hasMoved() const;
        virtual char getPieceChar() const;
};