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
    for(auto item : copy_board.getPieces()){
        createPiece(item->getCoords(), item->getColor(), item->getType());
    }
    update();
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

void Board::movePiece(Piece* target_piece, const Coordinates& final_coords){
    try {
        target_piece->movePiece(final_coords);
    } catch (std::invalid_argument& e) {
        // Checa se é um roque
        King* king = dynamic_cast<King*>(target_piece);
        if (king != NULL && final_coords.getCol() == (target_piece->getCoords().getCol() + 2 || target_piece->getCoords().getCol() - 2))
            if (king->validateCastle(final_coords))
                king->castle(final_coords);
            else
                throw e;
        else
            throw e;
    }
    //executar o en passant
    Pawn* pawn = dynamic_cast<Pawn*>(target_piece);
    if (pawn != nullptr && pawn->validateEnPassant(final_coords) == true)
    {
        int mult = target_piece->getColor() == White ? 1 : -1;
        target_piece->setCoords(final_coords);
        removePiece(Coordinates(final_coords.getRow()+mult, final_coords.getCol()));
    }

    if (isCapture(target_piece, final_coords)){
        removePiece(final_coords);
    }

    update();
}

bool Board::isCapture(Piece* target_piece, const Coordinates& final_coords) const{
    Piece* piece_end = getPiece(final_coords);
    if(piece_end==nullptr){
        return false;
    }
    return true;
}

std::string Board::boardToString() const{
    std::string output = "Estado atual do tabuleiro: \n";
    for(int i=0; i< 8; i++){
        output += "[ " + std::to_string(abs(i-8)) + " ][";
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
    output += "[   ][  a  b  c  d  e  f  g  h ]";
    return output;
}

Piece* Board::getPiece(const Coordinates& coords) const{
    int row = coords.getRow();
    int col = coords.getCol();
    return board_[row][col];
}

bool Board::isCheck(Color color) const {
    King* curr_player_king = nullptr;
    for(auto item : pieces_){
        if(item->getType()==KING && item->getColor()==color){
            curr_player_king = dynamic_cast<King*>(item);
            break;
        }
    }
    if(curr_player_king!=nullptr){
        return curr_player_king->isCheck();
    }
    std::string color_str = color==White?"branco":"preto";
    throw std::logic_error("Nenhum rei " + color_str + " encontrado.");
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
    for(auto row : board_){
        for(auto item : row){
            if(item==nullptr){
                continue;
            }
            delete item;
        }
    }
    pieces_ = {};
}

void Board::promotePawn(Piece* pawn, PieceType choice) {
    Coordinates auxCoords = pawn->getCoords();
    Color auxColor = pawn->getColor();
    if(pawn->getType()!=PAWN){
        throw std::invalid_argument("Só é possível promover peões.");
    }

    removePiece(pawn->getCoords());
    createPiece(auxCoords, auxColor, choice);
    update();
}