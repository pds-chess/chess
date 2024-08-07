#pragma once

#include <sstream>
#include <string>

class Coordinates {
 private:
  int row_;
  int column_;

 public:
  /**
   * @brief Construct a Coordinate.
   *
   * @param row represents the row in a matrix(7,7)
   * @param column represents the column in a matrix(7,7)
   */
  Coordinates(int row, int column);

  /**
   *
   * @brief Construct an empty Coordinate.
   */
  Coordinates();

  /**
   * @brief Return the row of a Coordinate.
   */
  int getRow() const;

  /**
   * @brief Return the column of a Coordinate.
   */
  int getCol() const;

  /**
   * @brief Transform a Coordinate into string.
   */
  std::string toString();
};
