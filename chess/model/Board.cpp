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
Board::~Board(){
    destroyPieces();
}

void Board::clearBoard(){
    board_ = std::vector<std::vector<Piece*>> (8, std::vector<Piece*>(8, nullptr));
}

void Board::initialize(){
    clearBoard();

    for(int j = 0; j<8; j++){
        createPiece(Coordinates(1,j), Black, PAWN);
        createPiece(Coordinates(6,j), White, PAWN);
    }
    createPiece(Coordinates(0,0), Black, ROOK);
    createPiece(Coordinates(0,7), Black, ROOK);
    createPiece(Coordinates(7,0), White, ROOK);
    createPiece(Coordinates(7,7), White, ROOK);

    createPiece(Coordinates(0,1), Black, KNIGHT);
    createPiece(Coordinates(0,6), Black, KNIGHT);
    createPiece(Coordinates(7,1), White, KNIGHT);
    createPiece(Coordinates(7,6), White, KNIGHT);

    createPiece(Coordinates(0,2), Black, BISHOP);
    createPiece(Coordinates(0,5), Black, BISHOP);
    createPiece(Coordinates(7,2), White, BISHOP);
    createPiece(Coordinates(7,5), White, BISHOP);

    createPiece(Coordinates(0,3), Black, QUEEN);
    createPiece(Coordinates(7,3), White, QUEEN);

    createPiece(Coordinates(0,4), Black, KING);
    createPiece(Coordinates(7,4), White, KING);

    update();
}

void Board::update(){
    pieces_ = {};
    for(auto row : board_){
        for(auto item : row){
            if(item != nullptr){
                pieces_.push_back(item);
            }
        }
    }
    clearBoard();

    for(auto piece : pieces_){
        int row = piece->getCoords().getRow();
        int col = piece->getCoords().getCol();
        board_[row][col] = piece;
    }
}

std::string Board::boardToString() const{
    std::string output = "Estado atual do tabuleiro: \n[ 1  2  3  4  5  6  7  8 ]\n";
    for(int i=0; i< 8; i++){
        output += "[ " + std::to_string(i) + " ]";
        for(int j =0; j< 8; j++){
            Piece* item = board_[i][j];
            if(item!=nullptr){
                output += " " + item->pieceToString();
                continue;
            }
            output += " __";
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