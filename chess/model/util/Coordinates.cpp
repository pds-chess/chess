#include "Coordinates.hpp"
#include <stdexcept>

Coordinates::Coordinates(int row, int column){
    if(row < 1 || row > 8){
        throw std::invalid_argument("Linha inválida.");
    }
    if(column < 1 || column > 8){
        throw std::invalid_argument("Coluna inválida.");
    }

    row_ = row-1;
    column_ = column-1;
}

int Coordinates::getCol() const{
    return column_;
}

int Coordinates::getRow() const{
    return row_;
}