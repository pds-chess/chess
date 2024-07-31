#pragma once

#include "Piece.hpp"
#include "Coordinates.hpp"

#include <list>
#include <string>
#include <vector>

class Board{
    private:
        std::vector<std::vector<Piece*>> board_;
        std::list<Piece*> pieces_;
        void clearBoard();
    public:
        Board();
        Board(const Board& copyBoard);
        void initialize();
        void update();
        std::vector<std::vector<Piece*>> getBoard() const;
        std::string boardToString() const;
        Piece* getPiece(const Coordinates& coords) const;
        void removePiece(const Coordinates& coords);
        std::list<Piece*> getPieces() const;
};