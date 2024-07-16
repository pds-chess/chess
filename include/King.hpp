#pragma once

#include "Piece.hpp"
#include "Rook.hpp"

class King: public Piece{
    private:
        bool moved_;
        bool short_castle(Coordinates final_coordinates) const;
    public:
        King(Coordinates initial_coords, Color color, Board* board);
        virtual bool validateMove(Coordinates final_coordinates) const;
        void movePiece(Coordinates final_coordinates);
        bool validateCastle(Coordinates final_coordinates) const;
        void castle(Coordinates final_coordinates);
        bool hasMoved() const;
        virtual char getPieceChar() const;
};