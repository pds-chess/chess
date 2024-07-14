#include "Pawn.hpp"

Pawn::Pawn(Coordinates initial_coords, Color color, Board *board)
    : Piece(initial_coords, color, board){
    moved_ = false;
};

bool Pawn::validateMove(Coordinates final_coordinates) const{
    int multiplier = 0;
    if (Piece::getColor())
        int multiplier = -1;
    else
        int multiplier = 1;
    int DeltaRow = (final_coordinates.getRow() - Piece::getCoords().getRow()) * multiplier;
    int DeltaCol = (final_coordinates.getCol() - Piece::getCoords().getCol()) * multiplier;
    if (DeltaRow > 0 && DeltaRow <= 2 && (DeltaCol == 0)){
        for (int i = 2; i <= 3 && (i < 3 || !moved_); i++)
            if (getBoard()->getPiece(Coordinates(Piece::getCoords().getRow() + i * multiplier, Piece::getCoords().getCol())) != nullptr)
                return false;
    }
    else if (getBoard()->getPiece(final_coordinates) != nullptr && getBoard()->getPiece(final_coordinates)->getColor() != Piece::getColor() && DeltaCol == 1 && DeltaRow == 1)
        return true;
    return false;
}

void Pawn::en_passant() {

}

char Pawn::getPieceChar() const{
    return 'P';
}