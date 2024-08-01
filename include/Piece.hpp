#pragma once

#include "Coordinates.hpp"
#include "Color.hpp"

class Board;

class Piece{
    private:
        Coordinates coords_;
        Color color_;
        const Board& board_; 
    public:
        Piece(const Coordinates& initial_coords, Color color, const Board& board);
        void movePiece(const Coordinates& final_coordinates);
        Coordinates getCoords() const;
        Color getColor() const;
        virtual bool validateMove(const Coordinates& final_coordinates) const = 0;
        std::string pieceToString() const;
        void setCoords(const Coordinates& coords);
    protected:
        virtual char getPieceChar() const = 0;
        const Board& getBoard() const;
};