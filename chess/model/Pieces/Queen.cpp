#include "Board.hpp"
#include "Queen.hpp"

Queen::Queen(const Coordinates& initial_coords, Color color, const  Board& board) : Piece(initial_coords, color, board) {

}

Queen::~Queen(){
    
}
        
bool Queen::validateMove(const Coordinates& final_coordinates) const {
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
        if (RowP==RowF && ColP < ColF) {
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
    for (int i=1, j=1;RowP+i*multiplier_i<8 && ColP+j*multiplier_j<8; i++, j++) {
        Piece* PieceF= getBoard().getPiece(Coordinates (RowP+i*multiplier_i,ColP+j*multiplier_j));
        if (PieceF==nullptr) {
             if (RowP+i*multiplier_i==RowF&&ColP+j*multiplier_j==ColF)
                 return true;
              else continue;
        } 
        if (PieceF!=nullptr)
        if (PieceF->getColor()!=getColor() &&RowP+i*multiplier_i==RowF&&ColP+j*multiplier_j==ColF) {
            return true;
            }
        if (PieceF!=nullptr)
            return false;
        }
    }
    return false;
    }

char Queen::getPieceChar() const{
        return 'Q';
}

PieceType Queen::getType() const{
    return QUEEN;
}
