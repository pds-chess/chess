#pragma once

#include "Piece.hpp"

class Pawn: Piece{
    private:
        bool moved_;
    public:
        Pawn(Coordinates initial_coords, Color color);
        bool validateMove(Coordinates final_coordinates) const;
        void en_passant();
};