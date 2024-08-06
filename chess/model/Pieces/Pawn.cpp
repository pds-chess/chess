#include "Pawn.hpp"

#include "Board.hpp"

Pawn::Pawn(const Coordinates& initial_coords, Color color, const Board& board)
    : Piece(initial_coords, color, board) {
  moved_ = false;
  movedTwice_ = false;
  initialRow_ = initial_coords.getRow();
}

Pawn::Pawn(const Pawn& pawn, const Board& board) 
: Piece(pawn.getCoords(), pawn.getColor(), board){
    moved_ = pawn.moved_;
    movedTwice_ = pawn.movedTwice_;
    initialRow_ = pawn.initialRow_;
    previousRow_ = pawn.previousRow_;
}

Pawn::~Pawn() {}

void Pawn::movePiece(const Coordinates& final_coordinates) {
  previousRow_ = getCoords().getRow();
  if (validateEnPassant(final_coordinates) == false)
    Piece::movePiece(final_coordinates);
  if (moved_ == true) movedTwice_ = true;
  moved_ = true;
}

bool Pawn::validateMove(const Coordinates& final_coordinates) const {
  int multiplier = 0;
  int DeltaRow = (final_coordinates.getRow() - getCoords().getRow());
  int DeltaCol = (final_coordinates.getCol() - getCoords().getCol());
  if (getColor() == White) {
    DeltaRow *= -1;
    multiplier = -1;
  } else
    multiplier = 1;
  if (final_coordinates.getCol() < getCoords().getCol()) DeltaCol *= -1;

  if (DeltaRow > 0 && DeltaRow <= 2 && (DeltaCol == 0)) {
    for (int i = 1; i <= 2 && (i < 2 || !moved_); i++)
      if (getBoard().getPiece(Coordinates(getCoords().getRow() + i * multiplier,
                                          getCoords().getCol())) != nullptr)
        return false;
      else if (getCoords().getRow() + i * multiplier ==
                   final_coordinates.getRow() &&
               getCoords().getCol() == final_coordinates.getCol())
        return true;
  } else if (getBoard().getPiece(final_coordinates) != nullptr &&
             getBoard().getPiece(final_coordinates)->getColor() != getColor() &&
             DeltaCol == 1 && DeltaRow == 1)
    return true;
  return false;
}

bool Pawn::validateEnPassant(const Coordinates& final_coordinates) const {
  int mult = getColor() == White ? 1 : -1;

  Piece* target = getBoard().getPiece(Coordinates(
      final_coordinates.getRow() + mult, final_coordinates.getCol()));
  Pawn* enemyPawn = dynamic_cast<Pawn*>(target);

  if (enemyPawn != nullptr && enemyPawn->movedTwice_ == false &&
      enemyPawn->previousRow_ == enemyPawn->initialRow_ &&
      enemyPawn->getColor() != getColor())
    return true;
  else
    return false;
}

char Pawn::getPieceChar() const { return 'P'; }

bool Pawn::validatePromotion() const {
  if ((getColor() == White && getCoords().getRow() == 0) ||
      (getColor() == Black && getCoords().getRow() == 7))
    return true;
  else
    return false;
}

PieceType Pawn::getType() const { return PAWN; }
