#pragma once

#include "Piece.hpp"

class Knight : public Piece {
 public:
  /**
   * @brief Construct the Knight.
   *
   * @param initial_coords Initial coordinates of the Piece e.g. (0,0).
   * @param color Color of the Piece e.g. White.
   * @param board Game board.
   */
  Knight(const Coordinates& initial_coords, Color color, const Board& board);

  /**
   * @brief Virtual destructor.
   */
  ~Knight();

  /**
   * @brief Validate the movement of Knight according to chess rule.
   * @param final_coordinates Coordinates witch Knight will try to move.
   * @return Returns true if the movement is valid and false otherwise.
   */
  bool validateMove(const Coordinates& final_coordinates) const override;
  
  /**
   * @brief Get the type of Piece e.g. KNIGHT.
   * @return Returns the Piece type.
   */
  PieceType getType() const override;

 protected:
  /**
   * @brief Get the char that represents the type of Piece e.g. 'N'.
   * @return Returns the Piece Char.
   */
  char getPieceChar() const override;
};
