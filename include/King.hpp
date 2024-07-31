#pragma once

#include "Piece.hpp"
#include "Rook.hpp"

class King: public Piece{
    private:
        bool moved_;
        bool short_castle(const Coordinates& final_coordinates) const;
    public:
        King(const Coordinates& initial_coords, Color color, const Board& board);
        virtual bool validateMove(const Coordinates& final_coordinates) const;
        void movePiece(const Coordinates& final_coordinates);
        bool validateCastle(const Coordinates& final_coordinates) const;
        void castle(const Coordinates& final_coordinates);
        bool hasMoved() const;
        virtual char getPieceChar() const;
};