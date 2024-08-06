#pragma once

#include "Piece.hpp"

class Pawn : public Piece {
 private:
  bool moved_;
  bool movedTwice_;
  int previousRow_;
  int initialRow_;

 public:
  /**
   * @brief Construct the Pawn.
   *
   * @param initial_coords Initial coordinates of the Piece e.g. (0,0).
   * @param color Color of the Piece e.g. White.
   * @param board Game board.
   */
  Pawn(const Coordinates& initial_coords, Color color, const Board& board);

  /**
   * @brief Construct a copy of a Pawn.
   *
   * @param pawn Pawn object that will be copied.
   * @param board Game board where the this copy will be placed.
   */
  Pawn(const Pawn& pawn, const Board& board);

  /**
   * @brief Virtual destructor
   */
  ~Pawn();

  /**
   * @brief Validate the movement of Pawn according to chess rule.
   * @param final_coordinates Coordinates witch Pawn will try to move.
   * @return Returns true if the movement is valid and false otherwise.
   */
  bool validateMove(const Coordinates& final_coordinates) const override;

  /**
   * @brief Override movePiece from Piece to set moved_ to true and movedtwice_
   * to true after the second movement.
   * @param final_coordinates Coordinates witch Pawn will try to move.
   */
  void movePiece(const Coordinates& final_coordinates) override;

  /**
   * @brief Checks is this pawn can be promoted in its current state.
   * @return Returns true if it can be promoted and false otherwise.
   */
  bool validatePromotion() const;

  /**
   * @brief Checks if this pawn can make an en Passant move to a position.
   * @return Returns true if this pawn can make an en Passant move to the chosen
   * position and false otherwise.
   */
  bool validateEnPassant(const Coordinates& final_coordinates) const;

  /**
   * @brief Get the type of Piece e.g. PAWN.
   * @return Returns the Piece type.
   */
  PieceType getType() const override;

 protected:
  /**
   * @brief Get the char that represents the type of Piece e.g. 'P'.
   * @return Returns the Piece Char.
   */
  char getPieceChar() const override;
};
