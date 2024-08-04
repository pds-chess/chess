#include "Rook.hpp"
#include "Board.hpp"

Rook::Rook(const Coordinates& initial_coords, Color color, const Board& board) : Piece(initial_coords, color, board){
    moved_ = false;
}

Rook::~Rook(){
    
}

void Rook::movePiece(Coordinates final_coordinates){
    Piece::movePiece(final_coordinates);
    moved_ = true;
}

PieceType Rook::getType() const{
    return ROOK;
}

bool Rook::validateMove(const Coordinates& final_coordinates) const{
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
    if (RowP==RowF && ColP < ColF) {
        multiplier_i=0;
        multiplier_j=1;
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

bool Rook::hasMoved() const{
    return moved_;
}

char Rook::getPieceChar() const{
    return 'R';
}
