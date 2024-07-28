#pragma once

#include "Piece.hpp"

class Pawn: public Piece{
    private:
        bool moved_;
        bool movedTwice_;
    public:
        Pawn(Coordinates initial_coords, Color color, Board* board);
        virtual bool validateMove(Coordinates final_coordinates) const;
        void movePiece(Coordinates final_coordinates);
        bool validateEnPassant(Coordinates final_coordinates);
        void enPassant(Coordinates final_coordinates);
        virtual char getPieceChar() const;
};