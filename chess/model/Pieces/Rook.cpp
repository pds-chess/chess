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
    if (ColP==ColF) {
        for (int i=2; RowF!=i+1 && i<=8; i++) {
            Piece* PieceF= getBoard()->getPiece(Coordinates (getCoords().getRow()+i, getCoords().getCol()));
            if (PieceF->getColor()!=getColor() && PieceF!=nullptr && PieceF->getCoords().getCol()==ColF && PieceF->getCoords().getRow()==RowF)
                return true;
            if (PieceF!=nullptr)
                return false;
        }
    }
    if (RowP==RowF) {
        for (int i=2; ColF!=i+1 && i<=8; i++) {
            Piece* PieceF= getBoard()->getPiece(Coordinates (getCoords().getRow(), getCoords().getCol()+i));
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
