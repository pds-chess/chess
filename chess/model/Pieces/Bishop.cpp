#pragma once

#include "Bishop.hpp"

class Bishop: Piece{
    public:
        Bishop(Coordinates initial_coords, Color color, Board* board) : Piece::Piece(initial_coords, color, *getBoard()) {
        };
        bool validateMove(Coordinates final_coordinates) const {
        int Secundary_Diagonal= Piece::getCoords().getRow() + Piece::getCoords().getCol();
        int Primary_Diagonal= Piece::getCoords().getRow() - Piece::getCoords().getCol();
        int RowF = final_coordinates.getRow(), ColF = final_coordinates.getCol();
        int RowP =Piece::getCoords().getRow(), ColP = Piece::getCoords().getCol();
        if (RowF+ColF==Secundary_Diagonal && RowF-ColF==Primary_Diagonal) {
            int multiplier_i=0, multiplier_j=0;
            if(RowP>RowF && ColP>ColF)
                int multiplier_i=-1, multiplier_j=-1;
            if(RowP<RowF && ColP<ColF)
                int multiplier_i=1, multiplier_j=1;
            if(RowP>RowF && ColP<ColF)
                int multiplier_i=-1, multiplier_j=1;
            if(RowP<RowF && ColP>ColF)
                int multiplier_i=1, multiplier_j=-1;
            for (int i=2, j=2;i<=8 && j<=8 && i!=RowF+multiplier_i && j!=ColF+multiplier_j; i++, j++) {
                Piece* PieceF= getBoard()->getPiece(Coordinates (RowP+i*multiplier_i,ColP+j*multiplier_j));
                if (PieceF->getColor()!=Piece::getColor() && PieceF!=nullptr && PieceF->getCoords().getCol()==ColF && PieceF->getCoords().getRow()==RowF)
                    return true;
                if (PieceF!=nullptr)
                     return false;
                }
            }
        };
};
