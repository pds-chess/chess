#pragma once

#include "Piece.hpp"
#include "Rook.hpp"

class King: public Piece{
    private:
        bool moved_;
    public:
        King(Coordinates initial_coords, Color color, Board* board);
        bool validateMove(Coordinates final_coordinates) const;
        void castle(Rook* rook);
        char getPieceChar() const;
};