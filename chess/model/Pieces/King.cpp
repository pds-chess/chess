#include "King.hpp"
#include "Board.hpp"

King::King(Coordinates initial_coords, Color color, Board* board) : Piece(initial_coords, color, board){
    moved_ = false;
}

void King::movePiece(Coordinates final_coordinates){
    Piece::movePiece(final_coordinates);
    moved_ = true;
}

bool King::validateMove(Coordinates final_coordinates) const{
    int DeltaRow = (final_coordinates.getRow() - getCoords().getRow());
    int DeltaCol = (final_coordinates.getCol() - getCoords().getCol());
    if (DeltaCol==1||DeltaRow==-1||DeltaCol==1||DeltaCol==-1) {
        Piece* PieceF= getBoard()->getPiece(Coordinates (final_coordinates.getRow(), final_coordinates.getCol()));
        if (PieceF==nullptr||PieceF->getColor()!=getColor())
        return true;
    }
    return false;
}

bool King::hasMoved() const{
    return moved_;
}

bool King::short_castle(Coordinates final_coordinates) const{
    bool short_castle = NULL;
        if (final_coordinates.getCol() == getCoords().getCol()+2)
            short_castle = true;
        else if (final_coordinates.getCol() == getCoords().getCol()-2)
            short_castle = false;
}

bool King::validateCastle(Coordinates final_coordinates) const{
    if (hasMoved())
        return false;
    else{        
        Rook* rook = nullptr;
        Piece* pieceCol_7 = getBoard()->getPiece(Coordinates(getCoords().getRow(), 7));
        Piece* pieceCol_0 = getBoard()->getPiece(Coordinates(getCoords().getRow(), 0));
        if (short_castle(final_coordinates) && dynamic_cast<Rook*>(pieceCol_7) != NULL)
        {
            rook = dynamic_cast<Rook*>(pieceCol_7);
            if (rook->hasMoved())
                return false;
            else{
                if (getBoard()->getPiece(Coordinates(getCoords().getRow(), getCoords().getCol()+1)) == nullptr &&
                getBoard()->getPiece(Coordinates(getCoords().getRow(), getCoords().getCol()+2)) == nullptr)  
                    return true;
                else
                    return false;
            }
        }else if (!short_castle(final_coordinates) && dynamic_cast<Rook*>(pieceCol_0) != NULL){
            rook = dynamic_cast<Rook*>(pieceCol_0);
            if (rook->hasMoved())
                return false;
            else{
                if (getBoard()->getPiece(Coordinates(getCoords().getRow(), getCoords().getCol()-1)) == nullptr &&
                    getBoard()->getPiece(Coordinates(getCoords().getRow(), getCoords().getCol()-2)) == nullptr &&
                    getBoard()->getPiece(Coordinates(getCoords().getRow(), getCoords().getCol()-3)) == nullptr)
                    return true;
                else
                    return false;
            }
        }else
            return false;
    }
}

void King::castle(Coordinates final_coordinates){
    Rook* rook = nullptr;
    Piece* pieceCol_7 = getBoard()->getPiece(Coordinates(getCoords().getRow(), 7));
    Piece* pieceCol_0 = getBoard()->getPiece(Coordinates(getCoords().getRow(), 0));

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

    bool isKingInCheck(const Board* board, Coordinates kingCoords, Color kingColor) {
        // Verificar ameaças diagonais (bispos, rainha)
        for (int dirRow = -1; dirRow <= 1; dirRow += 2) {
            for (int dirCol = -1; dirCol <= 1; dirCol += 2) {
                int row = kingCoords.getRow() + dirRow;
                int col = kingCoords.getCol() + dirCol;
                while (board->isValid(Coordinates(row, col))) {
                    Piece* piece = board->getPiece(Coordinates(row, col));
                    if (piece != nullptr) {
                        if (piece->getColor() != kingColor && (dynamic_cast<Bishop*>(piece) || dynamic_cast<Queen*>(piece))) {
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
            while (board->isValid(Coordinates(row, kingCoords.getCol()))) {
                Piece* piece = board->getPiece(Coordinates(row, kingCoords.getCol()));
                if (piece != nullptr) {
                    if (piece->getColor() != kingColor && (dynamic_cast<Rook*>(piece) || dynamic_cast<Queen*>(piece))) {
                        return true;
                    }
                    break;
                }
                row += dir;
            }

            // Verificar colunas
            int col = kingCoords.getCol() + dir;
            while (board->isValid(Coordinates(kingCoords.getRow(), col))) {
                Piece* piece = board->getPiece(Coordinates(kingCoords.getRow(), col));
                if (piece != nullptr) {
                    if (piece->getColor() != kingColor && (dynamic_cast<Rook*>(piece) || dynamic_cast<Queen*>(piece))) {
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
            Coordinates coords(kingCoords.getRow() + knightMoves[i][0], kingCoords.getCol() + knightMoves[i][1]);
            if (board->isValid(coords)) {
                Piece* piece = board->getPiece(coords);
                if (piece != nullptr && piece->getColor() != kingColor && dynamic_cast<Knight*>(piece)) {
                    return true;
                }
            }
        }

        // Verificar ameaças dos peões
        int pawnMoves[2][2];
        if (kingColor == WHITE) {
            pawnMoves[0][0] = -1; pawnMoves[0][1] = -1; // Peão branco atacando para cima e para a esquerda
            pawnMoves[1][0] = -1; pawnMoves[1][1] = 1;  // Peão branco atacando para cima e para a direita
        } else {
            pawnMoves[0][0] = 1; pawnMoves[0][1] = -1; // Peão preto atacando para baixo e para a esquerda
            pawnMoves[1][0] = 1; pawnMoves[1][1] = 1;  // Peão preto atacando para baixo e para a direita
        }

        for (int i = 0; i < 2; ++i) {
            Coordinates coords(kingCoords.getRow() + pawnMoves[i][0], kingCoords.getCol() + pawnMoves[i][1]);
            if (board->isValid(coords)) {
                Piece* piece = board->getPiece(coords);
                if (piece != nullptr && piece->getColor() != kingColor && dynamic_cast<Pawn*>(piece)) {
                    return true;
                }
            }
        }
    return false;
}