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
        void destroyPieces();
    public:
        Board();
        Board(const Board& copyBoard);
        void initialize();
        void update();
        std::string boardToString() const;
        bool isCheck(Color color) const;
        Piece* getPiece(const Coordinates& coords) const;
        void movePiece(Piece* target_piece, const Coordinates& coord);
        bool isCapture(Piece* target_piece, const Coordinates& final_coords) const;
        void removePiece(const Coordinates& coords);
        void createPiece(const Coordinates& coords, Color color, PieceType type);
        std::list<Piece*> getPieces() const;
        ~Board();
};