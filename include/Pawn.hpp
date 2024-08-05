#pragma once

#include "Piece.hpp"

class Pawn: public Piece{
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
   * @brief Override movePiece from Piece to set moved_ to true and movedtwice_ to true after the second movement.
   * @param final_coordinates Coordinates witch Pawn will try to move.
   */
        void movePiece(const Coordinates& final_coordinates) override;
        bool validatePromotion() const;
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
