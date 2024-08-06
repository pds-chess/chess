#include "Player.hpp"

Player::Player():Player("", White){

}

Player::Player(std::string name, Color color){
    name_ = name;
    color_ = color;
}

std::list<Piece*> Player::getPieces() const{
    return pieces_;
}

void Player::setPieces(std::list<Piece*> pieces){
    pieces_ = pieces;
}

Color Player::getplayerColor() const{
    return color_;
}

std::string Player::getPlayerName() const{
    return name_;
}

void Player::addCapturedPiece(PieceType piece) {
    capturedPieces_.push_back(piece);
}

std::list<PieceType> Player::getCapturedPieces() const {
    return capturedPieces_;
}