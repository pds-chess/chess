#include "Match.hpp"
#include <stdexcept>

Match::Match(std::string playerW, std::string playerB) {
    startGame(playerW, playerB);
}

void Match::startGame(std::string playerW, std::string playerB){
    board_ = Board();
    player_W_ = Player(playerW, White);
    player_B_ = Player(playerB, Black);
    current_turn_ = player_W_;
    game_state_ = inProgress;
}

std::string Match::startTurn(){
    if(!isDraw()){
        return board_.boardToString();
    }
    if(!isCheck()){
            game_state_ = Draw;
            return "Jogo finalizou em empate por afogamento.";
    }
    if(current_turn_.getplayerColor()==White){
        game_state_ = VictoryW;
        return "Chequemate! Vitória do jogador " + player_W_.getPlayerName();
    }
    return "Chequemate! Vitória do jogador " + player_B_.getPlayerName();
}

void Match::endTurn(){
    if(current_turn_.getplayerColor() == White){
        current_turn_ = player_B_;
    }
    else{
        current_turn_ = player_W_;
    }
    board_.update();
}

void Match::movePiece(int row_start, int col_start, int row_end, int col_end){
    Coordinates coord_start(row_start, col_start);
    Piece* target_piece = board_.getPiece(coord_start);

    if(target_piece==nullptr){
        throw std::invalid_argument("Nenhuma peça na posição inicial.");
    }

    if(target_piece->getColor()!= current_turn_.getplayerColor()){
        throw std::logic_error("Jogador incorreto.");
    }

    Coordinates final_coords(row_end, col_end);
    movePiece(target_piece, final_coords);

    endTurn();
}

void Match::movePiece(Piece* target_piece, Coordinates final_coords){
    Piece* piece_end = board_.getBoard()[final_coords.getCol()][final_coords.getRow()];
    if(piece_end != nullptr){
        if(target_piece->getColor() != piece_end->getColor()){
            board_.getBoard()[final_coords.getCol()][final_coords.getRow()] = nullptr;
        }
        else{
            //testa roque
            //. . .
        }
    }
    
    //testa en passant
    //. . .

    target_piece->movePiece(final_coords);
    if(isCheck()){
        throw std::logic_error("Rei estará em cheque.");
    }
}

bool Match::isDraw() const{

}

bool Match::isCheck() const{
    return false;
}