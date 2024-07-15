#pragma once

#include "Rook.hpp"
#include <stdexcept>

Rook::Rook(Coordinates initial_coords, Color color, Board* board) : Piece(initial_coords, color, board){
    moved_ = false;
};

void Rook::movePiece(Coordinates final_coordinates){
    if(!validateMove(final_coordinates)){
        throw std::invalid_argument("Movimento inválido");
    }
    coords_=final_coordinates;

    if (this->getCoords().getRow() !=  final_coordinates.getRow() || this->getCoords().getCol() !=  final_coordinates.getCol())
        moved_ = true;
}

bool Rook::validateMove(Coordinates final_coordinates) const{
    //<- isso tem que ser uma função (setMoved()) que é chamada em um overwrite da função movePiece dentro dessa classe.
}

bool Rook::hasMoved() const{
    return moved_;
}

char Rook::getPieceChar() const{
    return 'R';
}
