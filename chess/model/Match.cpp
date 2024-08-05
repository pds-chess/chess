#include "Match.hpp"
#include <stdexcept>
#include <iostream>
#include <map>

Match::Match(std::string playerW, std::string playerB): board_(Board()) {
    player_W_ = Player(playerW, White);
    player_B_ = Player(playerB, Black);
    startGame();
}

Gamestate Match::getGameState(){
    if(!isDraw()){
        return game_state_;
    }
    if (!board_.isCheck(current_turn_->getplayerColor())) {
        game_state_ = Draw;
    }
    else if (current_turn_->getplayerColor() == White) {
        game_state_ = VictoryW;
    }
    else{
        game_state_ = VictoryB;
    }
    return game_state_;
}

void Match::startGame(){
    //game_id_ = ;
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
    board_.update();
    updatePlayers();
}

void Match::movePiece(int row_start, int col_start, int row_end, int col_end){
    Coordinates coord_start(row_start, col_start);
    Piece* target_piece = board_.getPiece(coord_start);

    if (target_piece == nullptr) {
        throw std::invalid_argument("Nenhuma peça na posição inicial.");
    }

    if (target_piece->getColor() != current_turn_->getplayerColor()) {
        throw std::logic_error("Jogador incorreto.");
    }

    Coordinates final_coords(row_end, col_end);
    PieceType end_piece = NONE;
    if(board_.isCapture(target_piece, final_coords)){
        end_piece = board_.getPiece(final_coords)->getType();
    }
    
    board_.movePiece(target_piece, final_coords);

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
                if (item->validateMove(Coordinates(i, j))) {
                    return false;
                }
            }
        }
    }
    return true;
}

// void Match::simulateMove(const Coordinates& coord_start, const Coordinates& coord_end) const{
//     Board virtual_board = Board(board_);
//     virtual_board.getPieces();
// }

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

void Match::promotePawn(Pawn* pawn) {
    Coordinates auxCoords = pawn->getCoords();
    Color auxColor = pawn->getColor();
    
    char choice = 'p';
    std::cout << "Seu peão será promovido! Digite a letra correspondente a qual peça deseja promovê-lo: " << std::endl;
    std::cout << "Rainha - R" << std::endl;
    std::cout << "Torre - T" << std::endl;
    std::cout << "Bispo - B" << std::endl;
    std::cout << "Cavalo - C" << std::endl;
    std::cin >> choice;
    switch (choice) {
        case 'R':
            board_.removePiece(pawn->getCoords());
            board_.createPiece(auxCoords, auxColor, QUEEN);
            break;
        case 'T':
            board_.removePiece(pawn->getCoords());
            board_.createPiece(auxCoords, auxColor, ROOK);
            break;
        case 'B':
            board_.removePiece(pawn->getCoords());
            board_.createPiece(auxCoords, auxColor, BISHOP);
            break;
        case 'C':
            board_.removePiece(pawn->getCoords());
            board_.createPiece(auxCoords, auxColor, KNIGHT);
            break;
        default:
            std::cout << "Escolha inválida. Por padrão, o peão será promovido para Rainha" << std::endl;
            board_.removePiece(pawn->getCoords());
            board_.createPiece(auxCoords, auxColor, QUEEN);
            break;
    }
}

// Método para registrar um movimento
void Match::registerMove(Piece* target_piece, Coordinates final_coords) {
    Move move(target_piece->getCoords(),final_coords,current_turn_->getplayerColor(),current_turn_->getPlayerName(),game_id_);
    moves_.push_back(move);
    // if (game_state_ != inProgress)
    //     history_.saveMatch(moves_);
}

// Método para finalizar o jogo com empate
void Match::draw() {
    game_state_ = Draw;
}

// Método para desistência
void Match::resign() {
    if (current_turn_->getplayerColor() == White) {
        game_state_ = VictoryB;
    } else {
        game_state_ = VictoryW;
    }
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
        capturedPieces+= entry.second + "x ";
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
    }
    return capturedPieces;
}
