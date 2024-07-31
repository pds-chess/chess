#include "Match.hpp"
#include <stdexcept>
#include <iostream>
#include <Queen.hpp>
#include <Rook.hpp>
#include <Bishop.hpp>
#include <Knight.hpp>

Match::Match(std::string playerW, std::string playerB) {
    startGame(playerW, playerB);
}

void Match::startGame(std::string playerW, std::string playerB){
    //game_id_ = 
    board_ = Board();
    player_W_ = Player(playerW, White);
    player_B_ = Player(playerB, Black);
    updatePlayers();
    current_turn_ = &player_W_;
    game_state_ = inProgress;

    // Inicializando atributos de proposta de empate
    drawProposed = false;
    proposingPlayer = "";
}

std::string Match::startTurn(){
    if (!isDraw()) {
        return board_.boardToString();
    }
    if (!isCheck()) {
        game_state_ = Draw;
        return "Jogo finalizou em empate por afogamento.";
    }
    if (current_turn_->getplayerColor() == White) {
        game_state_ = VictoryW;
        return "Chequemate! Vitória do jogador " + player_W_.getPlayerName();
    }
    game_state_ = VictoryB;
    return "Chequemate! Vitória do jogador " + player_B_.getPlayerName();
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
    if (isCheck()) {
        throw std::logic_error("Rei estará em cheque.");
    }

    movePiece(target_piece, final_coords);

    endTurn();
}

void Match::movePiece(Piece* target_piece, Coordinates final_coords){
    Piece* piece_end = board_.getPiece(final_coords);

    // Testa en passant
    Pawn* pawn = dynamic_cast<Pawn*>(target_piece);
    if (pawn != NULL && pawn->validateEnPassant(final_coords) == true)
    {
        pawn->enPassant(final_coords);
        registerMove(target_piece, final_coords);
    }
    try {
        target_piece->movePiece(final_coords);
        registerMove(target_piece, final_coords);
    } catch (std::invalid_argument& e) {
        // Checa se é um roque
        King* king = dynamic_cast<King*>(target_piece);
        if (king != NULL && final_coords.getCol() == (target_piece->getCoords().getCol() + 2 || target_piece->getCoords().getCol() - 2))
            if (king->validateCastle(final_coords))
                king->castle(final_coords);
            else
                throw e;
    }

    // Promover o peão caso chegue ao fim do tabuleiro
    if (pawn != NULL && pawn->validatePromotion() == true)
        promotePawn(pawn);

    if (piece_end != nullptr) {
        board_.removePiece(final_coords);
    }
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

bool Match::isCheck() const {
    return false;
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

void Match::promotePawn(Piece* pawn) {
    Coordinates auxCoords = pawn->getCoords();
    Color auxColor = pawn->getColor();
    board_.removePiece(pawn->getCoords());
    
    char choice = NULL;
    std::cout << "Seu peão será promovido! Digite a letra correspondente a qual peça deseja promovê-lo: " << std::endl;
    std::cout << "Rainha - R" << std::endl;
    std::cout << "Torre - T" << std::endl;
    std::cout << "Bispo - B" << std::endl;
    std::cout << "Cavalo - C" << std::endl;
    while(choice != 'R' || choice != 'C' || choice != 'T' || choice != 'B')
    {
        std::cin >> choice;
        switch (choice) {
            case 'R':
                Queen(auxCoords, auxColor,&board_);
                break;
            case 'T':
                Rook(auxCoords, auxColor,&board_);
                break;
            case 'B':
                Bishop(auxCoords, auxColor,&board_);
                break;
            case 'C':
                Knight(auxCoords, auxColor,&board_);
                break;
            default:
                std::cout << "Escolha inválida. Favor, escolher uma das opções listadas" << std::endl;
                break;        
        }
    }
}

// Método para registrar um movimento
void Match::registerMove(Piece* target_piece, Coordinates final_coords) {
    std::string moves = target_piece->getCoords().toString() + " para " + final_coords.toString();
    Move move = Move(target_piece->getCoords(),final_coords,current_turn_->getplayerColor(),current_turn_->getPlayerName(), game_id_);
    moves_.push_back(moves);
    //history_.saveMove(move);
}

// Método para finalizar o jogo com empate
void Match::draw() {
    game_state_ = Draw;
}

// Métodos para gerenciamento de empate
void Match::proposeDraw(const std::string& player) {
    drawProposed = true;
    proposingPlayer = player;
}

void Match::confirmDraw(const std::string& player) {
    if (drawProposed && player != proposingPlayer) {
        draw();
        drawProposed = false;
        proposingPlayer = "";
    }
}

// Método para desistência
void Match::resign() {
    if (current_turn_->getplayerColor() == White) {
        game_state_ = VictoryB;
    } else {
        game_state_ = VictoryW;
    }
}
