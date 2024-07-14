#include "Piece.hpp"
#include <stdexcept>

Piece::Piece(Coordinates initial_coords, Color color, Board* board){
    coords_ = initial_coords;
    color_ = color;
    board_ = board;
}

void Piece::movePiece(Coordinates final_coordinates){
    if(!validateMove(final_coordinates)){
        throw std::invalid_argument("Movimento inválido");
    }
    coords_=final_coordinates;
}

Coordinates Piece::getCoords() const{
    return coords_;
}

Color Piece::getColor() const{
    return color_;
}

Board* Piece::getBoard() const{
    return board_;
}

std::string Piece::pieceToString() const{
    char pieceColor = color_==White?'w':'b';
    std::string output = "" + getPieceChar() + pieceColor;
    return output;
}