#pragma once

#include "Coordinates.hpp"
#include "Color.hpp"

#include <string>

struct Move{
    std::string origin_coordinates_;
    std::string final_coordinates_; 
    Color color_;
    std::string player_name_;
    int game_id_;
    
    Move(Coordinates origin_coords, Coordinates final_coords, Color player_color, std::string player_name, int game_id) : 
    origin_coordinates_(origin_coords.toString()), final_coordinates_(final_coords.toString()), color_(player_color), player_name_(player_name), game_id_(game_id){};
};
