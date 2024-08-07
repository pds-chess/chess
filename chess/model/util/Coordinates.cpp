#include "Coordinates.hpp"

#include <stdexcept>

Coordinates::Coordinates() {}

Coordinates::Coordinates(int row, int column) {
  if (row < 0 || row > 7) {
    throw std::invalid_argument("Linha inválida.");
  }
  if (column < 0 || column > 7) {
    throw std::invalid_argument("Coluna inválida.");
  }
  row_ = row;
  column_ = column;
}

int Coordinates::getRow() const { return row_; }

int Coordinates::getCol() const { return column_; }

std::string Coordinates::toString() {
  std::string output = "";
  char col = column_ + 97;
  output += col;
  output += std::to_string(abs(row_ - 8));
  return output;
}