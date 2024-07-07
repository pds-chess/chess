#pragma once

#include "Piece.hpp"

#include <string>
#include <list>

class Player{
    private:
    enum Color {White, Black};
    std::string name_;
    std::list<Piece*> pieces_;
    std::list<Piece*> captured_pieces_;
    public:
    void addPiece(Piece* piece);
    std::list<Piece*> getPieces() const;
    void removePiece(Piece* piece);
    Color getplayerColor() const;
    std::string getPlayerName() const;
    void addCapturedPiece(Piece* piece);
};