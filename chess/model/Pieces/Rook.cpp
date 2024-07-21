#pragma once

#include "Rook.hpp"

Rook::Rook(Coordinates initial_coords, Color color, Board* board) : Piece(initial_coords, color, board){
    moved_ = false;
};

void Rook::movePiece(Coordinates final_coordinates){
    Piece::movePiece(final_coordinates);
    moved_ = true;
}

bool Rook::validateMove(Coordinates final_coordinates) const{
    int RowF = final_coordinates.getRow(), ColF = final_coordinates.getCol();
    int RowP = getCoords().getRow(), ColP = getCoords().getCol();
    if(RowP==RowF||ColP==ColF) {
    int multiplier_i=0, multiplier_j=0;
    if (ColP==ColF && RowP < RowF) {
        multiplier_i=1;
        multiplier_j=0;
    }
    if (ColP==ColF && RowP > RowF) {
        multiplier_i=-1;
        multiplier_j=0;
    }
    if (RowP==RowF && ColP > ColF) {
        multiplier_i=0;
        multiplier_j=-1;
    }
    if (ColP==ColF && ColP < ColF) {
        multiplier_i=0;
        multiplier_j=1;
    }
     for (int i=2, j=2;i<=8 && j<=8 && i!=RowF+multiplier_i && j!=ColF+multiplier_j; i++, j++) {
            Piece* PieceF= getBoard()->getPiece(Coordinates (RowP+i*multiplier_i,ColP+j*multiplier_j));
            if (PieceF->getColor()!=getColor() && PieceF!=nullptr && PieceF->getCoords().getCol()==ColF && PieceF->getCoords().getRow()==RowF)
                return true;
            if (PieceF!=nullptr)
                return false;
    }
    }
    return false;
}

bool Rook::hasMoved() const{
    return moved_;
}

char Rook::getPieceChar() const{
    return 'R';
}
