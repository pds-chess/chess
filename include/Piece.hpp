#pragma once

#include "Coordinates.hpp"
#include "Color.hpp"
#include "Board.hpp"

class Piece{
    private:
        Coordinates coords_;
        Color color_;
        Board* board_; 
    public:
        Piece(Coordinates initial_coords, Color color, Board* board);
        void movePiece(Coordinates final_coordinates);
        Coordinates getCoords() const;
        Color getColor() const;
        virtual bool validateMove(Coordinates final_coordinates) const = 0;
    protected:
        Board* getBoard() const;
};