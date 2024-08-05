#pragma once

#include "Piece.hpp"

class Rook: public Piece{
    private:
        bool moved_;
    public:
    /**
   * @brief Construct the Rook.
   *
   * @param initial_coords Initial coordinates of the Piece e.g. (0,0).
   * @param color Color of the Piece e.g. White.
   * @param board Game board.
   */
        Rook(const Coordinates& initial_coords, Color color, const Board& board);
    /**
   * @brief Virtual destructor.
   */
        ~Rook();
    /**
   * @brief Validate the movement of Rook according to chess rule.
   * @param final_coordinates Coordinates witch Rook will try to move.
   * @return Returns true if the movement is valid and false otherwise.
   */
        bool validateMove(const Coordinates& final_coordinates) const override;
    /**
   * @brief Override movePiece from Piece to set moved_ to true.
   * @param final_coordinates Coordinates witch Rook will try to move.
   */
        void movePiece(const Coordinates& final_coordinates) override;
    /**
   * @brief Return if the Rook has moved.
   * @return Returns moved_.
   */
        bool hasMoved() const;
    /**
   * @brief Get the type of Piece e.g. ROOK.
   * @return Returns the Piece type.
   */
        PieceType getType() const override;
    protected:
    /**
   * @brief Get the char that represents the type of Piece e.g. 'R'.
   * @return Returns the Piece Char.
   */
        char getPieceChar() const override;
};
