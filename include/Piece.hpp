#pragma once

#include "Coordinates.hpp"
#include "Color.hpp"

class Piece{
    private:
        Coordinates coords_;
        Color color_;
        Board board_; 
    public:
        Piece(const Coordinates& initial_coords, Color color, const Board& board);
        void movePiece(const Coordinates& final_coordinates);
        Coordinates getCoords() const;
        Color getColor() const;
        virtual bool validateMove(const Coordinates& final_coordinates) const = 0;
        std::string pieceToString() const;
    protected:
        void setCoords(const Coordinates& coords);
        virtual char getPieceChar() const = 0;
        const Board& getBoard() const;
};