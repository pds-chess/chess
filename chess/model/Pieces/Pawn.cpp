#include "Pawn.hpp"
#include "Board.hpp"

Pawn::Pawn(const Coordinates& initial_coords, Color color, const Board& board)
    : Piece(initial_coords, color, board){
    moved_ = false;
    movedTwice_ = false;
    initialRow_ = initial_coords.getRow();
}

Pawn::~Pawn(){
    
}

void Pawn::movePiece(const Coordinates& final_coordinates){
    if(moved_ == true)
        movedTwice_ = true;
    moved_ = true;
    previousRow_ = getCoords().getRow();
    Piece::movePiece(final_coordinates);
}

bool Pawn::validateMove(const Coordinates& final_coordinates) const{
    int multiplier = 0, flag=0;
    int DeltaRow = (final_coordinates.getRow() - getCoords().getRow());
    int DeltaCol = (final_coordinates.getCol() - getCoords().getCol());
    if (getColor()==White) {
        DeltaRow*=-1;
        multiplier=-1;
        }
    else
        multiplier = 1;
    if(final_coordinates.getCol()<getCoords().getCol())
        DeltaCol*=-1;
    if (DeltaRow > 0 && DeltaRow <= 2 && (DeltaCol == 0)){
        for (int i = 1; i <=2 && (i < 2 || !moved_); i++)
            if (getBoard().getPiece(Coordinates(getCoords().getRow()+ i * multiplier, getCoords().getCol())) != nullptr)
                return false;
            else if (getCoords().getRow()+ i * multiplier==final_coordinates.getRow()&&getCoords().getCol()==final_coordinates.getCol())
                flag=1;
    }
    else if (getBoard().getPiece(final_coordinates) != nullptr && getBoard().getPiece(final_coordinates)->getColor() != getColor() && DeltaCol == 1 && DeltaRow == 1)
        return true;
    if(flag==1)
        return true;
    return false;
}

bool Pawn::validateEnPassant(Coordinates final_coordinates){
    int mult = 0;
    int finalRow = 0;
    int DeltaRow = (final_coordinates.getRow() - getCoords().getRow());
    int DeltaCol = (final_coordinates.getCol() - getCoords().getCol());
    if (getColor()==White) {
        DeltaRow*=-1;
        mult=-1;
        }
    else
        mult = 1;
    if(final_coordinates.getCol()<getCoords().getCol())
        DeltaCol*=-1;
    if (final_coordinates.getRow() == finalRow && getBoard().getPiece(final_coordinates) == nullptr && DeltaRow == 1 && DeltaCol == 1)
    {
        Piece* target = getBoard().getPiece(Coordinates(final_coordinates.getRow()-mult, final_coordinates.getCol()));
        Pawn* enemyPawn = dynamic_cast<Pawn*>(target);
        if (enemyPawn != NULL && enemyPawn->movedTwice_ == false && enemyPawn->previousRow_ == enemyPawn->initialRow_)
            return true;
        else
            return false;
    }else
        return false;
}

char Pawn::getPieceChar() const{
    return 'P';
}

bool Pawn::validatePromotion() const {
    if((getColor() == White && getCoords().getRow() == 0) || (getColor() == Black && getCoords().getRow() == 7))
        return true;
    else
        return false;
}

PieceType Pawn::getType() const{
    return PAWN;
}
