#include "History.hpp"
#include "Move.hpp"
#include "Coordinates.hpp"
#include "Color.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

History::History(std::string path) : path_to_file_(path) {}

void History::saveMove(Coordinates origin_coords, Coordinates final_coords, Color player_color, std::string player_name, int game_id) {
    std::ofstream file(path_to_file_, std::ios::app); // Abrir o arquivo em modo de adição (append)
    if (!file.is_open()) {
        throw std::runtime_error("Não foi possível abrir o arquivo de histórico.");
    }

    file << game_id << ","
         << origin_coords.toString() << ","
         << final_coords.toString() << ","
         << (player_color == White ? "White" : "Black") << ","
         << player_name << "\n";

    file.close();
}

std::list<Move> History::getMoves(int game_id) const {
    std::ifstream file(path_to_file_);
    if (!file.is_open()) {
        throw std::runtime_error("Não foi possível abrir o arquivo de histórico.");
    }

    std::list<Move> moves;
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        int id;
        Coordinates origin, destination;
        Color color;
        std::string player_name;

        std::getline(iss, token, ',');
        id = std::stoi(token);

        if (id != game_id) continue;

        std::getline(iss, token, ',');
        origin = Coordinates::fromString(token);

        std::getline(iss, token, ',');
        destination = Coordinates::fromString(token);

        std::getline(iss, token, ',');
        color = (token == "White") ? White : Black;

        std::getline(iss, token, ',');
        player_name = token;

        moves.emplace_back(origin, destination, color, player_name);
    }

    file.close();
    return moves;
}

std::list<int> History::getGames() const {
    std::ifstream file(path_to_file_);
    if (!file.is_open()) {
        throw std::runtime_error("Não foi possível abrir o arquivo de histórico.");
    }

    std::list<int> game_ids;
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        std::getline(iss, token, ',');

        int game_id = std::stoi(token);
        if (std::find(game_ids.begin(), game_ids.end(), game_id) == game_ids.end()) {
            game_ids.push_back(game_id);
        }
    }

    file.close();
    return game_ids;
}
