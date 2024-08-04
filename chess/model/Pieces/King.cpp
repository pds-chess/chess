#include "King.hpp"
#include "Board.hpp"

King::King(const Coordinates& initial_coords, Color color, const Board& board) : Piece(initial_coords, color, board){
    moved_ = false;
}

King::~King(){
    
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
    if(DeltaCol<0)
        DeltaCol*=-1;
    if(DeltaRow<0)
        DeltaRow*=-1;
    if (DeltaCol<=1&&DeltaRow<=1) {
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
        if (final_coordinates.getCol() == getCoords().getCol()+2)
            return true;
        if (final_coordinates.getCol() == getCoords().getCol()-2)
            return false;
}

bool King::validateCastle(const Coordinates& final_coordinates) const{       
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
    }
    if (!short_castle(final_coordinates) && dynamic_cast<Rook*>(pieceCol_0) != NULL)
    {
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

bool King::isCheck() {
    // Verificar ameaças diagonais (bispos, rainha)
    Coordinates kingCoords = getCoords();
    Board board = getBoard();
    Color kingColor = getColor();
    
    for (int dirRow = -1; dirRow <= 1; dirRow += 2) {
        for (int dirCol = -1; dirCol <= 1; dirCol += 2) {
            int row = kingCoords.getRow() + dirRow;
            int col = kingCoords.getCol() + dirCol;
            while (row >= 0 && row < 8 && col >= 0 && col < 8) {
                Piece* piece = board.getPiece(Coordinates(row, col));
                if (piece != nullptr) {
                    if (piece->getColor() != kingColor && (getType() == BISHOP || getType() == QUEEN)) {
                        return true;
                    }
                    break;
                }
                row += dirRow;
                col += dirCol;
            }
        }
    }

    // Verificar ameaças horizontais e verticais (torres, rainha)
    for (int dir = -1; dir <= 1; dir += 2) {
        // Verificar linhas
        int row = kingCoords.getRow() + dir;
        while (row >= 0 && row < 8) {
            Piece* piece = board.getPiece(Coordinates(row, kingCoords.getCol()));
            if (piece != nullptr) {
                if (piece->getColor() != kingColor && (getType() == ROOK || getType() == QUEEN)) {
                    return true;
                }
                break;
            }
            row += dir;
        }

        // Verificar colunas
        int col = kingCoords.getCol() + dir;
        while (col >= 0 && col < 8) {
            Piece* piece = board.getPiece(Coordinates(kingCoords.getRow(), col));
            if (piece != nullptr) {
                if (piece->getColor() != kingColor && (getType() == ROOK || getType() == QUEEN)) {
                    return true;
                }
                break;
            }
            col += dir;
        }
    }

    // Verificar ameaças do cavalo
    int knightMoves[8][2] = {
        {2, 1},  {2, -1},  {-2, 1},  {-2, -1},
        {1, 2},  {1, -2},  {-1, 2},  {-1, -2}
    };
    for (int i = 0; i < 8; ++i) {
        int row = kingCoords.getRow() + knightMoves[i][0];
        int col = kingCoords.getCol() + knightMoves[i][1];
        if (row >= 0 && row < 8 && col >= 0 && col < 8) {
            Piece* piece = board.getPiece(Coordinates(row, col));
            if (piece != nullptr && piece->getColor() != kingColor && getType() == KNIGHT) {
                return true;
            }
        }
    }

    // Verificar ameaças dos peões
    int pawnMoves[2][2];
    if (kingColor == White) {
        pawnMoves[0][0] = -1; pawnMoves[0][1] = -1; // Peão branco atacando para cima e para a esquerda
        pawnMoves[1][0] = -1; pawnMoves[1][1] = 1;  // Peão branco atacando para cima e para a direita
    } else {
        pawnMoves[0][0] = 1; pawnMoves[0][1] = -1; // Peão preto atacando para baixo e para a esquerda
        pawnMoves[1][0] = 1; pawnMoves[1][1] = 1;  // Peão preto atacando para baixo e para a direita
    }

    for (int i = 0; i < 2; ++i) {
        int row = kingCoords.getRow() + pawnMoves[i][0];
        int col = kingCoords.getCol() + pawnMoves[i][1];
        if (row >= 0 && row < 8 && col >= 0 && col < 8) {
            Piece* piece = board.getPiece(Coordinates(row, col));
            if (piece != nullptr && piece->getColor() != kingColor && getType() == PAWN) {
                return true;
            }
        }
    }
    return false;
}

PieceType King::getType() const{
    return KING;
}
