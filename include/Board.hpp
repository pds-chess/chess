#pragma once

#include "Piece.hpp"
#include "Coordinates.hpp"

#include <list>
#include <string>
#include <vector>

class Board{
    private:
        std::vector<std::vector<Piece*>> board_;
        std::list<Piece*> pieces_;

        /**
          * @brief Clear the board. 
          */
        void clearBoard();

        /**
          * @brief Delete the pieces. 
          */
        void destroyPieces();

        /**
          * @brief Create a copy of the piece.
          * @param piece. 
          */
        void createPiece(Piece* piece);
    public:
        /**
          * @brief Default Constructor. 
          */
        Board();

        /**
          * @brief Constructor.
          * @param copyBoard.
          */
        Board(const Board& copyBoard);

        /**
          * @brief Initializes the board pieces. 
          */                    
        void initialize();

        /**
          * @brief Update the state of the board based on the coordinates of the pieces in play. 
          */
        void update();

        /**
          * @brief Transform the current state of the board into a string.
          * @return Returns string
          */
        std::string boardToString() const;

        /**
          * @brief Is Check.
          * @param color.
          * @return Returns true (check) or false (no check).
          */
        bool isCheck(Color color) const;

        /**
          * @brief Get Piece.
          * @param coords.
          * @return Returns a list of pieces.
          */
        Piece* getPiece(const Coordinates& coords) const;

        /**
          * @brief Move Piece.
          * @param target_piece.
          * @param coord.
          */
        void movePiece(Piece* target_piece, const Coordinates& coord);

        /**
          * @brief Is Capture.
          * @param target_piece.
          * @param coords.
          * @return Returns true (piece can be captured) or false (piece can't be captured).
          */
        bool isCapture(Piece* target_piece, const Coordinates& final_coords) const;

        /**
          * @brief Remove a piece.
          * @param coords.
          */
        void removePiece(const Coordinates& coords);

        /**
          * @brief Create a new piece in the specified position.
          * @param coords.
          * @param color.
          * @param type Type of the piece.
          */
        void createPiece(const Coordinates& coords, Color color, PieceType type);

        /**
          * @brief Promote the pawn.          
          * @param pawn.
          * @param choice Option to choose.
          */
        void promotePawn(Piece* pawn, PieceType choice);
        
        std::list<Piece*> getPieces() const;

        /**
          * @brief Virtual destructor.
          */
        ~Board();
};