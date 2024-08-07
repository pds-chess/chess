#pragma once

#include "Coordinates.hpp"
#include "Color.hpp"
#include "PieceType.hpp"

class Board;

class Piece{
    private:
        Coordinates coords_;
        Color color_;
        const Board& board_;

    public:
        /**
          * @brief Constructor.
          * @param initial_coords.
          * @param color.
          * @param board.
          */
        Piece(const Coordinates& initial_coords, Color color, const Board& board);

        /**
          * @brief Virtual destructor.
          */
        virtual ~Piece();

        /**
          * @brief Move Piece.
          * @param final_coordinates.
          */
        virtual void movePiece(const Coordinates& final_coordinates);

        /**
          * @brief Get Coordinates.
          * @return Returns Coordinates (row, column).
          */
        Coordinates getCoords() const;

        /**
          * @brief Get Color.
          * @return Returns color.
          */
        Color getColor() const;

        /**
          * @brief Validate Move.
          * @return Returns true (valid move) or false (invalid move).
          */
        virtual bool validateMove(const Coordinates& final_coordinates) const = 0;

        /**
          * @brief Transform the current state of the piece into a string.
          * @return Returns string
          */
        std::string pieceToString() const;

        /**
          * @brief Set coordinates
          * @param coords.
          */
        void setCoords(const Coordinates& coords);

        /**
          * @brief get piece type.
          * @return Returns PieceType
          */
        virtual PieceType getType() const = 0;

    protected:
        /**
          * @brief get piece.
          * @return Returns char
          */
        virtual char getPieceChar() const = 0;

        /**
          * @brief Get Board.
          * @return Returns board.
          */
        const Board& getBoard() const;
};
