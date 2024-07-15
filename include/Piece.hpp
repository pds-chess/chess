#pragma once

#include "Coordinates.hpp"
#include "Color.hpp"
#include "Board.hpp"

class Piece{
    protected:
        Coordinates coords_;
        Color color_;
        Board* board_; 
    public:
        Piece(Coordinates initial_coords, Color color, Board* board);
        void movePiece(Coordinates final_coordinates);
        Coordinates getCoords() const;
        Color getColor() const;
        virtual bool validateMove(Coordinates final_coordinates) const = 0;
        std::string pieceToString() const;
    protected:
        virtual char getPieceChar() const = 0;
        Board* getBoard() const;
};