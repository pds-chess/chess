#pragma once

#include "Piece.hpp"

class Queen: Piece{
    public:
        Queen(Coordinates initial_coords, Color color);
        bool validateMove(Coordinates final_coordinates) const;
};