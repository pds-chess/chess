#pragma once

#include "Piece.hpp"
#include "Color.hpp"

#include <string>
#include <list>

class Player{
    private:
        Color color_;
        std::string name_;
        std::list<Piece*> pieces_;
    public:
        Player();
        Player(std::string name, Color color);
        void setPieces(std::list<Piece*> pieces_);
        std::list<Piece*> getPieces() const;
        Color getplayerColor() const;
        std::string getPlayerName() const;
};