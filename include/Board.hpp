#pragma once

#include "Piece.hpp"
#include "Coordinates.hpp"

#include <vector>
#include <string>

class Board{
    private:
        std::vector<std::vector<Piece*>> board;
        std::vector<Piece*> pieces;
    public:
        Board();
        void initialize();
        void update();
        std::vector<std::vector<Piece*>> getBoard();
        std::string boardToString();
        Piece* getPiece(Coordinates coords);
};