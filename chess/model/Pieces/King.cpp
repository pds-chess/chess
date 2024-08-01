#include "King.hpp"
#include "Board.hpp"

King::King(const Coordinates& initial_coords, Color color, const Board& board) : Piece(initial_coords, color, board){
    moved_ = false;
}

void King::movePiece(const Coordinates& final_coordinates){
    if (!hasMoved() && (final_coordinates.getCol() == 6 || final_coordinates.getCol() == 2))
        castle(final_coordinates);
    else
    Piece::movePiece(final_coordinates);
    
    moved_ = true;
}

bool King::validateMove(const Coordinates& final_coordinates) const{
    int DeltaRow = (final_coordinates.getRow() - getCoords().getRow());
    int DeltaCol = (final_coordinates.getCol() - getCoords().getCol());
    if (DeltaCol==1||DeltaRow==-1||DeltaCol==1||DeltaCol==-1) {
        Piece* PieceF= getBoard().getPiece(Coordinates (final_coordinates.getRow(), final_coordinates.getCol()));
        if (PieceF==nullptr||PieceF->getColor()!=getColor())
        return true;
    }

    if (!hasMoved() && (final_coordinates.getCol() == 6 || final_coordinates.getCol() == 2))
        return validateCastle(final_coordinates);
    
    return false;
}

bool King::hasMoved() const{
    return moved_;
}

bool King::short_castle(const Coordinates& final_coordinates) const{
    bool short_castle = NULL;
        if (final_coordinates.getCol() == getCoords().getCol()+2)
            short_castle = true;
        else if (final_coordinates.getCol() == getCoords().getCol()-2)
            short_castle = false;
}

bool King::validateCastle(const Coordinates& final_coordinates) const{
    if (hasMoved())
        return false;
    else{        
        Rook* rook = nullptr;
        Piece* pieceCol_7 = getBoard().getPiece(Coordinates(getCoords().getRow(), 7));
        Piece* pieceCol_0 = getBoard().getPiece(Coordinates(getCoords().getRow(), 0));
        if (short_castle(final_coordinates) && dynamic_cast<Rook*>(pieceCol_7) != NULL)
        {
            rook = dynamic_cast<Rook*>(pieceCol_7);
            if (rook->hasMoved())
                return false;
            else{
                if (getBoard().getPiece(Coordinates(getCoords().getRow(), getCoords().getCol()+1)) == nullptr &&
                getBoard().getPiece(Coordinates(getCoords().getRow(), getCoords().getCol()+2)) == nullptr)  
                    return true;
                else
                    return false;
            }
        }else if (!short_castle(final_coordinates) && dynamic_cast<Rook*>(pieceCol_0) != NULL){
            rook = dynamic_cast<Rook*>(pieceCol_0);
            if (rook->hasMoved())
                return false;
            else{
                if (getBoard().getPiece(Coordinates(getCoords().getRow(), getCoords().getCol()-1)) == nullptr &&
                    getBoard().getPiece(Coordinates(getCoords().getRow(), getCoords().getCol()-2)) == nullptr &&
                    getBoard().getPiece(Coordinates(getCoords().getRow(), getCoords().getCol()-3)) == nullptr)
                    return true;
                else
                    return false;
            }
        }else
            return false;
    }
}

void King::castle(const Coordinates& final_coordinates){
    Rook* rook = nullptr;
    Piece* pieceCol_7 = getBoard().getPiece(Coordinates(getCoords().getRow(), 7));
    Piece* pieceCol_0 = getBoard().getPiece(Coordinates(getCoords().getRow(), 0));

    if (short_castle(final_coordinates))
    { 
        rook = dynamic_cast<Rook*>(pieceCol_7);
        rook->movePiece(Coordinates(rook->getCoords().getRow(),rook->getCoords().getCol()-2));
        setCoords(final_coordinates);        
    }else{ 
        rook = dynamic_cast<Rook*>(pieceCol_0);
        rook->movePiece(Coordinates (rook->getCoords().getRow(),rook->getCoords().getCol()+3));
        setCoords(final_coordinates);
    }
}
    
char King::getPieceChar() const{
    return 'K';
}

PieceType King::getType() const{
    return KING;
}
