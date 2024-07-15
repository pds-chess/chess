#pragma once

#include "King.hpp"
#include <stdexcept>

King::King(Coordinates initial_coords, Color color, Board* board) : Piece(initial_coords, color, board){
    moved_ = false;
};

void King::movePiece(Coordinates final_coordinates){
    Piece::movePiece(final_coordinates);
    moved_ = true;
}

bool King::validateMove(Coordinates final_coordinates) const{
}

bool King::hasMoved() const{
    return moved_;
}

void King::castle(Rook* rook){
    if (!hasMoved() && !rook->hasMoved())
    {   
        bool short_castle_ = rook->getCoords().getCol() > getCoords().getCol();
        if (short_castle_)
        {
            if (getBoard()->getPiece(Coordinates(getCoords().getRow(), getCoords().getCol()+1)) == nullptr &&
                getBoard()->getPiece(Coordinates(getCoords().getRow(), getCoords().getCol()+2)) == nullptr)
            {   
                rook->movePiece(Coordinates (rook->getCoords().getRow(),rook->getCoords().getCol()-2));
                if (getColor() == Black)
                    King(Coordinates(0,6), Color(Black), getBoard());
                else
                    King(Coordinates(7,6), Color(White),getBoard());
                getBoard()->removePiece(getCoords());
            }else
                throw std::invalid_argument("Movimento inválido");
        }else{
            if (getBoard()->getPiece(Coordinates(getCoords().getRow(), getCoords().getCol()-1)) == nullptr &&
                getBoard()->getPiece(Coordinates(getCoords().getRow(), getCoords().getCol()-2)) == nullptr &&
                getBoard()->getPiece(Coordinates(getCoords().getRow(), getCoords().getCol()-3)) == nullptr)
            {   
                rook->movePiece(Coordinates (rook->getCoords().getRow(),rook->getCoords().getCol()+3));
                if (getColor() == Black)
                    King(Coordinates(0,2), Color(Black), getBoard());
                else
                    King(Coordinates(7,2), Color(White),getBoard());
                getBoard()->removePiece(getCoords());
            }else
                throw std::invalid_argument("Movimento inválido");
        }
    }else
        throw std::invalid_argument("Movimento inválido");
    
    //endTurn();
}
    
char King::getPieceChar() const{
    return 'K';
}

