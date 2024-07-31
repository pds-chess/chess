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
        History(std::string path);
        void saveMove(Move move);
        std::list<Move> getMoves(int game_id) const;
        std::list<int> getGames() const;
};