#pragma once#include "Piece.hpp"

#include "Piece.hpp"

class Bishop: Piece{
    public:
        Bishop(Coordinates initial_coords, Color color);
        bool validateMove(Coordinates final_coordinates) const;
};