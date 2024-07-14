#pragma once

#include "Rook.hpp"

Rook::Rook(Coordinates initial_coords, Color color, Board* board) : Piece(initial_coords, color, board){
    moved_ = false;
};

bool Rook::validateMove(Coordinates final_coordinates) {

    //...Implementação normal da função

    if (this->getCoords().getRow() !=  final_coordinates.getRow() || this->getCoords().getCol() !=  final_coordinates.getCol())
        this->moved_ = true;
    //Fim da função validateMove
}

bool Rook::hasMoved() const{
    return moved_;
}

char Rook::getPieceChar() const{
    return 'R';
}
