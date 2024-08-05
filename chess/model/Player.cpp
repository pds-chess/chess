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

// void Player::showCapturedPieces() {
//     // Obtemos a lista de todas as peças no tabuleiro
//     std::list<Piece*> allPieces = player_->getPieces();

//     // Criamos um conjunto para verificar quais peças estão no tabuleiro
//     unordered_map<string, Piece*> pieceMap;
//     for (Piece* piece : allPieces) {
//         pieceMap[piece->getType() + piece->getPlayerName()] = piece;
//     }

//     // Obtemos a lista de peças capturadas
//     list<Piece*> capturedPieces = player_->getCapturedPieces();
//     unordered_map<string, int> capturedCount;

//     // Contamos as peças capturadas que não estão no tabuleiro
//     for (Piece* piece : capturedPieces) {
//         string key = piece->getType() + piece->getPlayerName();
//         if (pieceMap.find(key) == pieceMap.end()) {
//             capturedCount[piece->getType()]++;
//         }
//     }

//     // Imprimimos o resumo das peças capturadas
//     std::cout << "Peças adversárias capturadas:" << std::endl;
//     for (const auto& entry : capturedCount) {
//         std::cout << entry.second << "x " << entry.first << std::endl;
//     }
// }