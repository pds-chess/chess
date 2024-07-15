#pragma once

#include "Piece.hpp"
#include "Rook.hpp"

class King: public Piece{
    private:
        bool moved_;
    public:
        King(Coordinates initial_coords, Color color, Board* board);
        virtual bool validateMove(Coordinates final_coordinates) const;
        void movePiece(Coordinates final_coordinates);
        void castle(Rook* rook);
        bool hasMoved() const;
        virtual char getPieceChar() const;
};