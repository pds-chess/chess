#pragma once

#include "Match.hpp"
#include <string>

class Console
{
private:
    /**
      * @brief Create a new game.
      *
      * @param playerA.
      * @param playerB.
      */
    void createNewGame(std::string playerA, std::string playerB);

    /**
      * @brief Print the menu with the options to make a move, propose a draw and see all opposing pieces that have been captured.
      * @param match.
      */    
    void printGameActions(Match& match);

    /**
      * @brief Print the final result of the match.
      * @param match.
      */ 
    void printGameEnd(Match& match);

    /**
      * @brief Print the history of all matches.     
      */ 
    void printMatchHistory();

    /**
      * @brief Print the history of a specific match. 
      * @param matchId Specific match.
      */
    void printMatch(int matchId);
    
    /**
      * @brief Propose a draw.
      * @param match.
      */
    void handleDraw(Match& match);

    /**
      * @brief Print all opposing pieces that have been captured.
      * @param match.
      */        
    void showCapturedPieces(Match& match);

    /**
      * @brief Move Piece.
      * @param match.
      */
    void movePiece(Match& match);

    /**
      * @brief Choose what the new piece will be and call the promote pawn function.
      * @param match.
      * @param row_end End row in the last move.
      * @param col_end End column in the last move.
      */
    void promote(Match& match, int row_end, int col_end);

public:
    /**
      * @brief Default constructor that launches the game on the console.     
      */    
    Console();
    
    /**
      * @brief Print the menu with the options to create a new game and view history.    
      */
    void printMenu();

    /**
      * @brief Virtual destructor.
      */
    ~Console();
};
