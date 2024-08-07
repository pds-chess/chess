#include "PieceFactory.hpp"

#include "Bishop.hpp"
#include "King.hpp"
#include "Knight.hpp"
#include "Pawn.hpp"
#include "Queen.hpp"
#include "Rook.hpp"

PieceFactory::PieceFactory() {}

Piece* PieceFactory::createPiece(const Coordinates& coords, Color color,
                                 const Board& board, PieceType type) {
  if (type == PAWN) {
    return new Pawn(coords, color, board);
  }
  if (type == ROOK) {
    return new Rook(coords, color, board);
  }
  if (type == KNIGHT) {
    return new Knight(coords, color, board);
  }
  if (type == BISHOP) {
    return new Bishop(coords, color, board);
  }
  if (type == QUEEN) {
    return new Queen(coords, color, board);
  }
  if (type == KING) {
    return new King(coords, color, board);
  }
  return nullptr;
}

Piece* PieceFactory::createPiece(Piece* piece, const Board& board) {
  if (piece->getType() == PAWN) {
    Pawn* old_pawn = dynamic_cast<Pawn*>(piece);
    return new Pawn(*old_pawn, board);
  }
  return createPiece(piece->getCoords(), piece->getColor(), board,
                     piece->getType());
}