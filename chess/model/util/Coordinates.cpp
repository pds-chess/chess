#include "Coordinates.hpp"

#include <stdexcept>

Coordinates::Coordinates() {}

Coordinates::Coordinates(int row, int column){
    if(row < 0 || row > 7){
        throw std::invalid_argument("Linha inválida.");
    }
    if(column < 0 || column > 7){
        throw std::invalid_argument("Coluna inválida.");
    }
    row_ = row;
    column_ = column;
}

int Coordinates::getRow() const{
    return row_;
}

int  Coordinates::getCol() const{
    return column_;
}

std::string Coordinates::toString() {
    return std::to_string(row_) + "," + std::to_string(column_);
}

void Coordinates::fromString(const std::string& str) {
    std::istringstream iss(str);
    std::string token;

    if (std::getline(iss, token, ',')) {
        row_ = std::stoi(token);
    } else {
        throw std::invalid_argument("String format is incorrect for Coordinates.");
    }

    if (std::getline(iss, token, ',')) {
        column_ = std::stoi(token);
    } else {
        throw std::invalid_argument("String format is incorrect for Coordinates.");
    }
}