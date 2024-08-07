#pragma once

#include <list>
#include <string>

#include "Color.hpp"
#include "Coordinates.hpp"
#include "Move.hpp"

class History {
 private:
  const std::string path_to_file_ = "./matches.txt";

  /**
   * @brief return all the moves of a especified match.
   *
   * @param game_id the identifier of a match.
   */
  std::list<Move> getMovesFile(int game_id) const;

 public:
  /**
   * @brief Construct match history, with every move done until the end.
   */
  History();

  /**
   * @brief Save the match identifier and all the moves done.
   *
   * @param moves a list with all the moves that has occured in the match.
   */
  void saveMatch(std::list<Move> moves);

  std::string getMoves(int game_id) const;

  /**
   * @brief return all the games played.
   */
  std::list<int> getGames() const;
};