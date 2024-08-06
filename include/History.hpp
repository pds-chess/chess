#pragma once

#include "Move.hpp"
#include "Coordinates.hpp"
#include "Color.hpp"

#include <string>
#include <list>

class History{
private:
    const std::string path_to_file_;
public:
/**
   * @brief Construct match history, with every move done until the end.
   *
   * @param path represents where that history will be saved. 
   */
        History(std::string path);
/**
   * @brief Save the match identifier and all the moves done.
   *
   * @param moves a list with all the moves that has occured in the match.
   */
        void saveMatch(std::list<Move> moves);
/**
   * @brief return all the moves of a especified match.
   *
   * @param game_id the identifier of a match.
   */
        std::list<Move> getMoves(int game_id) const;
/**
   * @brief return all the games played.
   */
        std::list<int> getGames() const;
};