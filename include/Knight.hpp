#pragma once

#include "Piece.hpp"

class Knight: Piece{
    public:
        Knight(Coordinates initial_coords, Color color, Board board);
        bool validateMove(Coordinates final_coordinates) const;
};