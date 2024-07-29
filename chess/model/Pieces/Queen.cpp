#include "Board.hpp"
#include "Queen.hpp"

Queen::Queen(Coordinates initial_coords, Color color, Board* board) : Piece(initial_coords, color, board) {

        }
        
bool Queen::validateMove(Coordinates final_coordinates) const {
    int Secundary_Diagonal= getCoords().getRow() + getCoords().getCol();
    int Primary_Diagonal= getCoords().getRow() - getCoords().getCol();
    int RowF = final_coordinates.getRow(), ColF = final_coordinates.getCol();
    int RowP = getCoords().getRow(), ColP = getCoords().getCol();
    if (RowF+ColF==Secundary_Diagonal || RowF-ColF==Primary_Diagonal||RowP==RowF||ColP==ColF) {
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
        if(RowP>RowF && ColP>ColF) {
            multiplier_i=-1;
            multiplier_j=-1;
        }
        if(RowP<RowF && ColP<ColF) {
            multiplier_i=1;
            multiplier_j=1;
        }
        if(RowP>RowF && ColP<ColF) {
            multiplier_i=-1;
            multiplier_j=1;
        }
        if(RowP<RowF && ColP>ColF) {
            multiplier_i=1;
            multiplier_j=-1;
    }
    for (int i=2, j=2;i<=8 && j<=8; i++, j++) {
        Piece* PieceF= getBoard()->getPiece(Coordinates (RowP+i*multiplier_i,ColP+j*multiplier_j));
        if (((PieceF->getColor()!=getColor() && PieceF!=nullptr)||PieceF==nullptr) && PieceF->getCoords().getCol()==ColF && PieceF->getCoords().getRow()==RowF)
            return true;
        if (PieceF!=nullptr)
            return false;
    }
    
    }
    return false;
}

char Queen::getPieceChar() const{
        return 'Q';
}
