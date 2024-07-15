#pragma once

#include "King.hpp"
#include <stdexcept>

King::King(Coordinates initial_coords, Color color, Board* board) : Piece(initial_coords, color, board){
    moved_ = false;
};

void King::movePiece(Coordinates final_coordinates){
    Piece::movePiece(final_coordinates);

    if (this->getCoords().getRow() !=  final_coordinates.getRow() || this->getCoords().getCol() !=  final_coordinates.getCol())
        moved_ = true;
}

bool King::validateMove(Coordinates final_coordinates) const{
}

bool King::hasMoved() const{
    return moved_;
}

void King::castle(Rook* rook){
    bool king_side_ = rook->getCoords().getCol() - getCoords().getCol();
    if (!hasMoved() && !rook->hasMoved())
    {
        
    }
    
}

char King::getPieceChar() const{
    return 'K';
}

