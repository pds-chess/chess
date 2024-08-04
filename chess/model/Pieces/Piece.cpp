#include "Piece.hpp"
#include "Board.hpp"
#include <stdexcept>

Piece::Piece(const Coordinates& initial_coords, Color color, const Board& board) : board_(board){
    coords_ = initial_coords;
    color_ = color;
}

Piece::~Piece(){
    
}

void Piece::setCoords(const Coordinates& coords){
    coords_ = coords;
}

void Piece::movePiece(const Coordinates& final_coordinates){
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

const Board& Piece::getBoard() const{
    return board_;
}

std::string Piece::pieceToString() const{
    char pieceColor = color_==White?'w':'b';
    std::string output = "";
    output +=  + getPieceChar();
    output += pieceColor;
    return output;
}