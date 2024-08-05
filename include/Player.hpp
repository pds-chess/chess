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
        std::list<PieceType> capturedPieces_;
    public:
        Player();
        Player(std::string name, Color color);
        void setPieces(std::list<Piece*> pieces);
        std::list<Piece*> getPieces() const;
        Color getplayerColor() const;
        std::string getPlayerName() const;
        // Método para saber as peças capturadas por um jogador
        void addCapturedPiece(PieceType piece);
        std::list<PieceType> getCapturedPieces() const;
};