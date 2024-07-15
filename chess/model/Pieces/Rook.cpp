#pragma once

#include "Rook.hpp"
#include <stdexcept>

Rook::Rook(Coordinates initial_coords, Color color, Board* board) : Piece(initial_coords, color, board){
    moved_ = false;
};

void Rook::movePiece(Coordinates final_coordinates){
    Piece::movePiece(final_coordinates);

    if (this->getCoords().getRow() !=  final_coordinates.getRow() || this->getCoords().getCol() !=  final_coordinates.getCol())
        moved_ = true;
}

bool Rook::validateMove(Coordinates final_coordinates) const{
}

bool Rook::hasMoved() const{
    return moved_;
}

char Rook::getPieceChar() const{
    return 'R';
}
