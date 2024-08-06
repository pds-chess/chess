#pragma once

#include "Piece.hpp"
#include "Rook.hpp"

class King : public Piece {
 private:
  bool moved_;
  bool short_castle(const Coordinates& final_coordinates) const;

 public:
  /**
   * @brief Construct the King.
   *
   * @param initial_coords Initial coordinates of the Piece e.g. (0,0).
   * @param color Color of the Piece e.g. White.
   * @param board Game board.
   */
  King(const Coordinates& initial_coords, Color color, const Board& board);

  /**
   * @brief Virtual destructor.
   */
  ~King();

  /**
   * @brief Validate the movement of King according to the basic King movement
   * chess rule.
   * @param final_coordinates Coordinates witch King will try to move.
   * @return Returns true if the movement is valid and false otherwise.
   */
  bool validateMove(const Coordinates& final_coordinates) const override;

  /**
   * @brief Override movePiece from Piece to check castle and set moved_ to
   * true.
   * @param final_coordinates Coordinates witch King will try to move.
   */
  void movePiece(const Coordinates& final_coordinates) override;

  bool validateCastle(const Coordinates& final_coordinates) const;

  void castle(const Coordinates& final_coordinates);

  bool hasMoved() const;

  bool isCheck();

  /**
   * @brief Get the type of Piece e.g. KING.
   * @return Returns the Piece type.
   */
  PieceType getType() const override;

 protected:
  /**
   * @brief Get the char that represents the type of Piece e.g. 'K'.
   * @return Returns the Piece Char.
   */
  char getPieceChar() const override;
};
