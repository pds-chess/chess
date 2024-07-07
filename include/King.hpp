#pragma once

#include "Piece.hpp"
#include "Rook.hpp"

class Rook: Piece{
    private:
        bool moved_;
    public:
        Rook(Coordinates initial_coords, Color color);
        bool validateMove(Coordinates final_coordinates) const;
        void castle(Rook* rook);
        bool isChecked() const;
};