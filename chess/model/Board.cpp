#include "Board.hpp"
#include "Pawn.hpp"
#include "Rook.hpp"
#include "Knight.hpp"
#include "Bishop.hpp"
#include "Queen.hpp"
#include "King.hpp"
#include "Color.hpp"

Board::Board(){
    initialize();
}

void Board::clearBoard(){
        board_ = std::vector<std::vector<Piece*>> (8, std::vector<Piece*>(8, nullptr));
}

void Board::initialize(){
    clearBoard();
    for(int j = 0; j<8; j++){
        board_[1][j] = &(Pawn(Coordinates(1,j), Black, this));
        board_[6][j] = &(Pawn(Coordinates(1,j), White, this));
    }
    board_[0][0] = &(Rook(Coordinates(0,0), Black, this));
    board_[0][7] = &(Rook(Coordinates(0,7), Black, this));
    board_[7][0] = &(Rook(Coordinates(7,0), White, this));
    board_[7][7] = &(Rook(Coordinates(7,7), White, this));

    board_[0][1] = &(Knight(Coordinates(0,1), Black, this));
    board_[0][6] = &(Knight(Coordinates(0,6), Black, this));
    board_[7][1] = &(Knight(Coordinates(7,1), White, this));
    board_[7][6] = &(Knight(Coordinates(7,6), White, this));

    board_[0][2] = &(Bishop(Coordinates(0,2), Black, this));
    board_[0][5] = &(Bishop(Coordinates(0,5), Black, this));
    board_[7][2] = &(Bishop(Coordinates(7,2), White, this));
    board_[7][5] = &(Bishop(Coordinates(7,5), White, this));

    board_[0][3] = &(Queen(Coordinates(0,3), Black, this));
    board_[7][3] = &(Queen(Coordinates(7,3), White, this));

    board_[0][4] = &(King(Coordinates(0,4), Black, this));
    board_[7][4] = &(King(Coordinates(7,4), White, this));

    update();
}

void Board::update(){
    std::vector<Piece*> pieces;
    for(auto row : board_){
        for(auto item : row){
            if(item != nullptr){
                pieces.push_back(item);
            }
        }
    }
    clearBoard();

    for(auto piece : pieces){
        int row = piece->getCoords().getRow();
        int col = piece->getCoords().getCol();
        board_[row][col] = piece;
    }
}

std::vector<std::vector<Piece*>> Board::getBoard() const{
    return board_;
}

std::string Board::boardToString() const{
    std::string output = "Estado atual do tabuleiro: \n";
    for(auto row: board_){
        output += "[";
        for(auto item: row){
            if(item!=nullptr){
                output += " " + item->pieceToString();
                continue;
            }
            output += " _";
        }
        output += " ]\n";
    }
    return output;
}

Piece* Board::getPiece(Coordinates coords) const{
    int row = coords.getRow();
    int col = coords.getCol();
    return board_[row][col];
}

void Board::removePiece(Coordinates coords){
    int row = coords.getRow();
    int col = coords.getCol();
    board_[row][col] = nullptr;
}