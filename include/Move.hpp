#pragma once

#include "Coordinates.hpp"
#include "Color.hpp"

#include <string>

class Move{
  private:
    std::string origin_coordinates_;
    std::string final_coordinates_; 
    Color color_;
    std::string player_name_;
    int game_id_;

    public:
        Move(Coordinates origin_coords, Coordinates final_coords, Color player_color, std::string player_name, int game_id);
        void saveMove(std::string file_name);
};
