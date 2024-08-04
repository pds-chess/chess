#pragma once

#include "Piece.hpp"

class Rook: public Piece{
    private:
        bool moved_;
    public:
        Rook(const Coordinates& initial_coords, Color color, const Board& board);
        ~Rook();
        bool validateMove(const Coordinates& final_coordinates) const override;
        void movePiece(Coordinates final_coordinates);
        bool hasMoved() const;
        PieceType getType() const override;
    protected:
        char getPieceChar() const override;
};