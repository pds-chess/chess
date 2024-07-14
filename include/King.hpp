#pragma once

#include "Piece.hpp"
#include "Rook.hpp"

class King: Piece{
    private:
        bool moved_;
    public:
        King(Coordinates initial_coords, Color color, Board* board);
        bool validateMove(Coordinates final_coordinates);
        void castle(Rook* rook);
        bool hasMoved() const;
        char getPieceChar() const;
};