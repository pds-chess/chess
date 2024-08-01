#include "Board.hpp"
#include "Pawn.hpp"
#include "Rook.hpp"
#include "Knight.hpp"
#include "Bishop.hpp"
#include "Queen.hpp"
#include "King.hpp"
#include "Color.hpp"
#include "PieceFactory.hpp"

#include <stdexcept>

Board::Board(){
    initialize();
}

Board::Board(const Board& copy_board){
    clearBoard();
    // for(int i = 0; i <8; i++){
    //     for(int j =0; j< 8; j++){
    //         board_[i][j] = copy_board.getBoard()[i][j];
    //     }
    // }
}

void Board::clearBoard(){
    board_ = std::vector<std::vector<Piece*>> (8, std::vector<Piece*>(8, nullptr));
}

void Board::initialize(){
    clearBoard();

    PieceFactory creator;
    for(int j = 0; j<8; j++){
        board_[1][j] = creator.createPiece(Coordinates(1,j), Black, *this, PAWN);
        board_[6][j] = creator.createPiece(Coordinates(1,j), White, *this, PAWN);
    }
    board_[0][0] = creator.createPiece(Coordinates(0,0), Black, *this, ROOK);
    board_[0][7] = creator.createPiece(Coordinates(0,7), Black, *this, ROOK);
    board_[7][0] = creator.createPiece(Coordinates(7,0), White, *this, ROOK);
    board_[7][7] = creator.createPiece(Coordinates(7,7), White, *this, ROOK);

    board_[0][1] = creator.createPiece(Coordinates(0,1), Black, *this, KNIGHT);
    board_[0][6] = creator.createPiece(Coordinates(0,6), Black, *this, KNIGHT);
    board_[7][1] = creator.createPiece(Coordinates(7,1), White, *this, KNIGHT);
    board_[7][6] = creator.createPiece(Coordinates(7,6), White, *this, KNIGHT);

    board_[0][2] = creator.createPiece(Coordinates(0,2), Black, *this, BISHOP);
    board_[0][5] = creator.createPiece(Coordinates(0,5), Black, *this, BISHOP);
    board_[7][2] = creator.createPiece(Coordinates(7,2), White, *this, BISHOP);
    board_[7][5] = creator.createPiece(Coordinates(7,5), White, *this, BISHOP);

    board_[0][3] = creator.createPiece(Coordinates(0,3), Black, *this, QUEEN);
    board_[7][3] = creator.createPiece(Coordinates(7,3), White, *this, QUEEN);

    board_[0][4] = creator.createPiece(Coordinates(0,4), Black, *this, KING);
    board_[7][4] = creator.createPiece(Coordinates(7,4), White, *this, KING);

    update();
}

void Board::update(){
    std::list<Piece*> pieces;
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

Piece* Board::getPiece(const Coordinates& coords) const{
    int row = coords.getRow();
    int col = coords.getCol();
    return board_[row][col];
}

void Board::removePiece(const Coordinates& coords){
    int row = coords.getRow();
    int col = coords.getCol();
    delete board_[row][col];
    board_[row][col] = nullptr;
}

std::list<Piece*> Board::getPieces() const{
    return pieces_;
}

void Board::createPiece(const Coordinates& coords, Color color, PieceType type){
    if(getPiece(coords)!=nullptr){
        throw std::logic_error("Não é possível criar uma peça em um espaço ocupado.");
    }

    PieceFactory creator;
    int row = coords.getRow();
    int col = coords.getCol();
    board_[row][col] = creator.createPiece(coords, color, *this, type);
}

void Board::destroyPieces(){
    for(auto item : getPieces()){
        delete item;
    }
}