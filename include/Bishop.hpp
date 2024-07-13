#pragma once

#include "Piece.hpp"

class Bishop: Piece{
    public:
        Bishop(Coordinates initial_coords, Color color, Board board);
        bool validateMove(Coordinates final_coordinates) const;
};