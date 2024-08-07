#pragma once

#include <list>
#include <string>

#include "Color.hpp"
#include "Piece.hpp"

class Player {
 private:
  Color color_;
  std::string name_;
  std::list<Piece*> pieces_;
  std::list<PieceType> capturedPieces_;

 public:
  /**
   * @brief Construct an empty Player.
   */
  Player();

  /**
   * @brief Construct a Player.
   *
   * @param name The name that the Player has written.
   * @param color The color of the pieces that the Player will play.
   */
  Player(std::string name, Color color);

  /**
   * @brief Set the player can have on the board.
   *
   * @param pieces A list with all the pieces the Player can move in a game.
   */
  void setPieces(std::list<Piece*> pieces);

  /**
   * @brief Return a list with all the pieces the player have on the board.
   */
  std::list<Piece*> getPieces() const;

  /**
   * @brief Return the color of Player's pieces.
   */
  Color getplayerColor() const;

  /**
   * @brief Return the name of the Player.
   */
  std::string getPlayerName() const;

  /**
   * @brief Add the piece that the player has captured into a list.
   */
  void addCapturedPiece(PieceType piece);

  /**
   * @brief Return the list of the captured pieces.
   */
  std::list<PieceType> getCapturedPieces() const;
};