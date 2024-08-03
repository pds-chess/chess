#include "PieceFactory.hpp"
#include "Pawn.hpp"
#include "Rook.hpp"
#include "Knight.hpp"
#include "Bishop.hpp"
#include "Queen.hpp"
#include "King.hpp"

PieceFactory::PieceFactory(){
}

Piece* PieceFactory::createPiece(const Coordinates& coords, Color color, const Board& board, PieceType type){
    if(type==PAWN){
        return new Pawn(coords, color, board);
    }
    if(type==ROOK){
        return new Rook(coords, color, board);
    }
    if(type==KNIGHT){
        return new Knight(coords, color, board);
    }
    if(type==BISHOP){
        return new Bishop(coords, color, board);
    }
    if(type==QUEEN){
        return new Queen(coords, color, board);
    }
    if(type==KING){
        return new King(coords, color, board);
    }
    return nullptr;
}