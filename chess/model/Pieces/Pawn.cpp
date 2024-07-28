#include "Pawn.hpp"
#include "Board.hpp"

Pawn::Pawn(Coordinates initial_coords, Color color, Board *board)
    : Piece(initial_coords, color, board){
    moved_ = false;
    movedTwice_ = false;
    initialRow_ = initial_coords.getRow();
}

void Pawn::movePiece(Coordinates final_coordinates){
    previousRow_ = getCoords().getRow();
    Piece::movePiece(final_coordinates);
    if(moved_ == true)
        movedTwice_ = true;
    moved_ = true;
}

bool Pawn::validateMove(Coordinates final_coordinates) const{
    int multiplier = 0;
    if (getColor()==Black)
        multiplier = -1;
    else
        multiplier = 1;
    int DeltaRow = (final_coordinates.getRow() - getCoords().getRow()) * multiplier;
    int DeltaCol = (final_coordinates.getCol() - getCoords().getCol()) * multiplier;
    if (DeltaRow > 0 && DeltaRow <= 2 && (DeltaCol == 0)){
        for (int i = 2; i <= 3 && (i < 3 || !moved_); i++)
            if (getBoard()->getPiece(Coordinates(getCoords().getRow() + i * multiplier, getCoords().getCol())) != nullptr)
                return false;
    }
    else if (getBoard()->getPiece(final_coordinates) != nullptr && getBoard()->getPiece(final_coordinates)->getColor() != getColor() && DeltaCol == 1 && DeltaRow == 1)
        return true;
    return false;
}

bool Pawn::validateEnPassant(Coordinates final_coordinates){
    int mult = 0;
    int finalRow = 0;
    if (getColor()==Black){
        mult = -1;
        finalRow = 5;
    }else{
        mult = 1;
        finalRow = 2;
    }
    int DeltaRow = (final_coordinates.getRow() - getCoords().getRow()) * mult;
    int DeltaCol = (final_coordinates.getCol() - getCoords().getCol()) * mult;
    if (final_coordinates.getRow() == finalRow && getBoard()->getPiece(final_coordinates) == nullptr && DeltaRow == 1 && DeltaCol == 1)
    {
        Piece* target = getBoard()->getPiece(Coordinates(final_coordinates.getRow()-mult, final_coordinates.getCol()));
        Pawn* enemyPawn = dynamic_cast<Pawn*>(target);
        if (enemyPawn != NULL && enemyPawn->movedTwice_ == false && enemyPawn->previousRow_ == enemyPawn->initialRow_)
            return true;
        else
            return false;
    }else
        return false;
}

void Pawn::enPassant(Coordinates final_coordinates) {
    int mult = 0;
    if (getColor()==Black)
        mult = -1;
    else
        mult = 1;
    setCoords(final_coordinates);
    getBoard()->removePiece(Coordinates(final_coordinates.getRow()-mult, final_coordinates.getCol()));
}

char Pawn::getPieceChar() const{
    return 'P';
}