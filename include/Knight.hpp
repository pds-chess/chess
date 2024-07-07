#pragma once

#include "Piece.hpp"

class Knight: Piece{
    public:
        Knight(Coordinates initial_coords, Color color);
        bool validateMove(Coordinates final_coordinates) const;
};