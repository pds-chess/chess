#pragma once

#include "Piece.hpp"

class Rook: Piece{
    private:
        bool moved_;
    public:
        Rook(Coordinates initial_coords, Color color, Board* board);
        bool validateMove(Coordinates final_coordinates);
        bool hasMoved() const;
        char getPieceChar() const;
};