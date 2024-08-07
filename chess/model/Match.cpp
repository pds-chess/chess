#include "Match.hpp"
#include <stdexcept>
#include <iostream>
#include <map>
#include <algorithm>

Match::Match(std::string playerW, std::string playerB): board_(Board()) {
    player_W_ = Player(playerW, White);
    player_B_ = Player(playerB, Black);
    startGame();
}

Gamestate Match::getGameState(){
    
    if(game_state_!=inProgress){
        
        return game_state_;
    }
    if(!isDraw()){
        return inProgress;
    }

    if (!board_.isCheck(current_turn_->getplayerColor())) {
        game_state_ = Draw;
    }
    else if (current_turn_->getplayerColor() == Black) {
        game_state_ = VictoryW;
    }
    else{
        game_state_ = VictoryB;
    }
    History history;
    history.saveMatch(moves_);
    return game_state_;
}

void Match::startGame(){
    History history_;
    auto games = history_.getGames();
    game_id_ = (*std::max_element(games.begin(), games.end()))+1;
    current_turn_ = &player_W_;
    game_state_ = inProgress;
    updatePlayers();
}


std::string Match::boardToString() const{
    return board_.boardToString();
}

void Match::endTurn(){
    if (current_turn_->getplayerColor() == White) {
        current_turn_ = &player_B_;
    } else {
        current_turn_ = &player_W_;
    }

    updatePlayers();
}

Piece* Match::getPieceInGame(int row, int col) const{
    Coordinates target_coord(row, col);
    Piece* target_piece = board_.getPiece(target_coord);
    if(target_piece==nullptr){
        throw std::invalid_argument("Nenhuma peça na posição requerida.");
    }
    return target_piece;
}

bool Match::isPromote(int row_end, int col_end) const{
    Piece* target_piece = getPieceInGame(row_end, col_end);

    Pawn* target_pawn = nullptr;
    if(target_piece->getType()!=PAWN){
        return false;
    }
    target_pawn = dynamic_cast<Pawn*>(target_piece);

    return target_pawn->validatePromotion();
}

void Match::promotePawn(int row, int col, PieceType type){
    Piece* target_piece = getPieceInGame(row, col);
    board_.promotePawn(target_piece, type);
}

void Match::movePiece(int row_start, int col_start, int row_end, int col_end){
    Piece* target_piece = getPieceInGame(row_start, col_start);

    if (target_piece->getColor() != current_turn_->getplayerColor()) {
        throw std::logic_error("Jogador incorreto.");
    }

    Coordinates final_coords(row_end, col_end);
    PieceType end_piece = NONE;
    if(board_.isCapture(target_piece, final_coords)){
        Pawn* pawn = dynamic_cast<Pawn*>(target_piece);
        if (pawn != nullptr && pawn->validateEnPassant(final_coords) == true){
            int mult = target_piece->getColor() == White ? 1 : -1;
            end_piece = board_.getPiece(Coordinates(final_coords.getRow()+mult, final_coords.getCol()))->getType();
        }else
            end_piece = board_.getPiece(final_coords)->getType();
    }

    simulateMove(Coordinates(row_start, col_start), final_coords);
    board_.movePiece(target_piece, final_coords);
    registerMove(target_piece, final_coords);

    if(end_piece!=NONE){
        current_turn_->addCapturedPiece(end_piece);
    }

    endTurn();
}

bool Match::isDraw() const{
    for (auto item : current_turn_->getPieces()) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (item->getCoords().getRow() == i && item->getCoords().getCol() == i) {
                    continue;
                }
                try{
                    if (simulateMove(Coordinates(item->getCoords().getRow(), item->getCoords().getCol()), Coordinates(i, j))) {
                        return false;
                    }
                } catch(std::invalid_argument& e){
                    continue;
                }
            }
        }
    }
    return true;
}

bool Match::simulateMove(const Coordinates& coord_start, const Coordinates& coord_end) const{
    Board virtual_board = Board(board_);
    Piece* target_piece = virtual_board.getPiece(coord_start);
    virtual_board.movePiece(target_piece, coord_end);
    if(virtual_board.isCheck(current_turn_->getplayerColor())){
        throw std::invalid_argument("O rei não pode ficar em cheque.");
    }
    return true;
}

void Match::updatePlayers(){
    std::list<Piece*> white_pieces, black_pieces;
    for (auto item : board_.getPieces()) {
        if (item->getColor() == White) {
            white_pieces.push_back(item);
        } else {
            black_pieces.push_back(item);
        }
    }
    player_W_.setPieces(white_pieces);
    player_B_.setPieces(black_pieces);
}

// Método para registrar um movimento
void Match::registerMove(Piece* target_piece, Coordinates final_coords) {
    Move move(target_piece->getCoords(),final_coords,current_turn_->getplayerColor(),current_turn_->getPlayerName(),game_id_);
    moves_.push_back(move);
}

// Método para finalizar o jogo com empate
void Match::draw() {
    game_state_ = Draw;
    History history;
    history.saveMatch(moves_);
}

// Método para desistência
void Match::resign() {
    if (current_turn_->getplayerColor() == White) {
        game_state_ = VictoryB;
    } else {
        game_state_ = VictoryW;
    }
    History history;
    history.saveMatch(moves_);
}

std::string Match::getCurrentPlayerName() const{
    return current_turn_->getPlayerName();
}

std::string Match::showCapturedPieces() {
    std::map<PieceType, int> capturedCount;
    std::string capturedPieces="Peças adversárias capturadas: ";

    for (PieceType piece : current_turn_->getCapturedPieces()) {
        if (capturedCount.find(piece) != capturedCount.end()) {
            capturedCount[piece]++;
        }
        else capturedCount[piece]=1;
    }

    // Imprimimos o resumo das peças capturadas
    for (const auto& entry : capturedCount) {
        capturedPieces += "\n" + std::to_string(entry.second) + "x ";
        if (entry.first==ROOK)
            capturedPieces+="Rook";
        if (entry.first==PAWN)
            capturedPieces+="Pawn";
        if (entry.first==KNIGHT)
            capturedPieces+="Knight";
        if (entry.first==BISHOP)
            capturedPieces+="Bishop";
        if (entry.first==QUEEN)
            capturedPieces+="Queen";
        if (entry.first==KING)
            capturedPieces+="King";
        if (entry.second>1)
            capturedPieces+="s";
        capturedPieces+="\n";
    }
    return capturedPieces;
}
