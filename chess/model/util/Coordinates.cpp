#include "Coordinates.hpp"
#include <stdexcept>

Coordinates::Coordinates(int row, int column){
    if(row < 0 || row > 7){
        throw std::invalid_argument("Linha inválida.");
    }
    if(column < 0 || column > 7){
        throw std::invalid_argument("Coluna inválida.");
    }
}

Coordinates::Coordinates():Coordinates(0,0){
}

int Coordinates::getCol() const{
    return column_;
}

int Coordinates::getRow() const{
    return row_;
}