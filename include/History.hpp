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
        void saveMove(Coordinates origin_coords, Coordinates final_coords, Color player_color, std::string player_name, int game_id);
        std::list<Move> getMoves(int game_id) const;
        std::list<int> getGames() const;
};