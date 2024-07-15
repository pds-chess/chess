#pragma once

#include "King.hpp"

King::King(Coordinates initial_coords, Color color, Board* board) : Piece(initial_coords, color, board){
    moved_ = false;
};

bool King::validateMove(Coordinates final_coordinates) const{

    //...Implementação normal da função

    if (this->getCoords().getRow() !=  final_coordinates.getRow() || this->getCoords().getCol() !=  final_coordinates.getCol())
        this->moved_ = true; //Ler comentário no rook e fazer o mesmo aqui
    //Fim da função validateMove
}

bool King::hasMoved() const{
    return moved_;
}

void King::castle(Rook* rook){
    // bool king_side_ = rook->getCoords().getCol() - this->getCoords().getCol();
    if (!this->hasMoved() && !rook->hasMoved())
    {
        
    }
    
}

char King::getPieceChar() const{
    return 'K';
}

