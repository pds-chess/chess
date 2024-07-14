#pragma once

#include "Piece.hpp"
#include "Coordinates.hpp"

#include <vector>
#include <string>

class Board{
    private:
        std::vector<std::vector<Piece*>> board_;
        std::vector<Piece*> pieces_;
        void clearBoard();
    public:
        Board();
        void initialize();
        void update();
        std::vector<std::vector<Piece*>> getBoard() const;
        std::string boardToString() const;
        Piece* getPiece(Coordinates coords) const;
        void removePiece(Coordinates coords);
};