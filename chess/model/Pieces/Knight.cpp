#include "Board.hpp"
#include "Knight.hpp"


Knight::Knight(const Coordinates& initial_coords, Color color, const Board& board) : Piece(initial_coords, color, board) {

}
bool Knight::validateMove(const Coordinates& final_coordinates) const{
    int DeltaRow = (final_coordinates.getRow() - getCoords().getRow());
    int DeltaCol = (final_coordinates.getCol() - getCoords().getCol());
    if(DeltaCol<0)
    DeltaCol*=-1;
    if(DeltaRow<0)
    DeltaRow*=-1;
    if(DeltaCol+DeltaRow==3) {
        Piece* PieceF= getBoard().getPiece(Coordinates (final_coordinates.getRow(), final_coordinates.getCol()));
        if (PieceF==nullptr||PieceF->getColor()!=getColor())
        return true;
    }
    return false;
}
char Knight::getPieceChar() const {
    return 'N';
}

PieceType Knight::getType() const{
    return KNIGHT;
}
