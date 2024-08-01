#pragma once

#include "Piece.hpp"

class Pawn: public Piece{
    private:
        bool moved_;
        bool movedTwice_;
        int previousRow_;
        int initialRow_;
    public:
        Pawn(const Coordinates& initial_coords, Color color, const Board& board);
        virtual bool validateMove(const Coordinates& final_coordinates) const;
        void movePiece(Coordinates final_coordinates);
        bool validatePromotion() const;
        bool validateEnPassant(Coordinates final_coordinates);
        virtual char getPieceChar() const;
};