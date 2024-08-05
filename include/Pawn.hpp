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
        ~Pawn();
        bool validateMove(const Coordinates& final_coordinates) const override;
        void movePiece(const Coordinates& final_coordinates) override;
        bool validatePromotion() const;
        bool validateEnPassant(const Coordinates& final_coordinates) const;
        PieceType getType() const override;
    protected:
        char getPieceChar() const override;
};