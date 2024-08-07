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
          * @return Coordinates (row, column).
          */
        Coordinates getCoords() const;

        /**
          * @brief Get Color.
          * @return Color.
          */
        Color getColor() const;

        /**
          * @brief Validate Move.
          * @return True (valid move) or false (invalid move).
          */
        virtual bool validateMove(const Coordinates& final_coordinates) const = 0;

        /**
          * @brief Transform the current state of the piece into a string.
          * @return String
          */
        std::string pieceToString() const;

        /**
          * @brief Set coordinates
          * @param coords.
          */
        void setCoords(const Coordinates& coords);

        /**
          * @brief get piece type.
          * @return PieceType
          */
        virtual PieceType getType() const = 0;

    protected:
        /**
          * @brief get piece.
          * @return char
          */
        virtual char getPieceChar() const = 0;

        /**
          * @brief Provide read-only access to the game board.
          * @return A constant reference to the Board object.
          */
        const Board& getBoard() const;
};
